#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "../include/util.h"
#include "../include/button.h"
extern MainSettings settings;
extern Point screenCenter;
extern void sayHello();

enum State {
  MAIN_MENU,
  PAUSE_MENU,
  RUNNING,
};


class App {
  private:
    State state = MAIN_MENU;
    bool running = true;
    Button* startButton;
    Button* optionsButton;
    Button* exitButton;
    SDL_Window* window;
    SDL_Renderer* renderer;
  public:
    App() {};
    ~App();
    int Init();
    void MainMenu();
    int Error();
    void HandleEvents();
    void Draw();
    bool Running();
    void Quit();
};

int App::Error() {
    std::cout << "Error initializing" << SDL_GetError() << std::endl;
    return 1;
}

int App::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return this->Error();
    }

    if (TTF_Init() < 0) {
      std::cout << "Error initializing text library" << TTF_GetError() << std::endl;
      return 1;
    }

    int result = SDL_CreateWindowAndRenderer(settings.SCREEN_WIDTH, settings.SCREEN_HEIGHT, NULL, &window, &renderer);
    if (result != 0) {
        return this->Error();
    }

    return 0;
}
void App::MainMenu() {
    startButton = new Button("Start", sayHello);
    startButton->SetForegroundColor(255,255,255);
    startButton->SetSize(100, 100);
    startButton->SetPoint(screenCenter.x, screenCenter.y - 120);

    optionsButton = new Button("Options", sayHello);
    optionsButton->SetForegroundColor(255,255,255);
    optionsButton->SetSize(100,100);
    optionsButton->SetPoint(screenCenter.x, screenCenter.y);

    exitButton = new Button("Exit");
    exitButton->SetForegroundColor(255,255,255);
    exitButton->SetSize(100,100);
    exitButton->SetPoint(screenCenter.x, screenCenter.y + 120);
}

void App::HandleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
      switch (e.type) {
        case SDL_QUIT:
          this->running = false;
        case SDL_MOUSEBUTTONDOWN:
            if (startButton->InBounds(e.button.x, e.button.y)) {
              startButton->Click();
            }
            if (optionsButton->InBounds(e.button.x, e.button.y)) {
              //starttton.Click();
              optionsButton->Click();
            }
            if (exitButton->InBounds(e.button.x, e.button.y)) {
              this->running = false;
            }
        }
    }
}

void App::Draw() {
    if (this->running == false) {
      return;
    }
    if (state == MAIN_MENU) {
      if (startButton->RenderButton(renderer) != 0 || startButton->Render(renderer) != 0) {
        this->running = false;
      };
      if (optionsButton->Render(renderer) != 0) {
        this->running = false;
      };
      if (exitButton->Render(renderer) != 0) {
        this->running = false;
      };
    }

    SDL_RenderPresent(renderer);
      this->running = true;
}

bool App::Running() {
  return this->running;
}

void App::Quit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    TTF_Quit();
    SDL_Quit();
}

App::~App() {
  delete startButton;
  delete optionsButton;
  delete exitButton;
}

