#include <iostream>
#include <SDL.h>
#include "../include/button.h"
#include "../include/util.h"
#include <SDL_ttf.h>

using namespace std;
int FPS = 60;
SDL_Window *window;
SDL_Renderer* renderer;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

int error() {
    cout << "Error initializing" << SDL_GetError() << endl;
    system("pause");
    return 1;
}

int init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return error();
    }

    if (TTF_Init() < 0) {
      cout << "Error initializing text library" << TTF_GetError() << endl;
      return 1;
    }

    int result = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, NULL, &window, &renderer);
    if (result != 0) {
        return error();
    }
    return 0;
}

void destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    TTF_Quit();
    SDL_Quit();
}

void sayHello() {
  SDL_Log("Hello, world!");
}

bool loop() {
    SDL_Event e;
    Point screenCenter = getScreenCenter(SCREEN_WIDTH, SCREEN_HEIGHT);
    Button startButton("Start", sayHello);
    startButton.SetForegroundColor(255,255,255);
    startButton.SetSize(100, 100);
    startButton.SetPoint(screenCenter.x, screenCenter.y - 120);

    Button optionsButton("Options", sayHello);
    optionsButton.SetForegroundColor(255,255,255);
    optionsButton.SetSize(100,100);
    optionsButton.SetPoint(screenCenter.x, screenCenter.y);

    Button exitButton("Exit", sayHello);
    exitButton.SetForegroundColor(255,255,255);
    exitButton.SetSize(100,100);
    exitButton.SetPoint(screenCenter.x, screenCenter.y + 120);


    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 120);
    //SDL_RenderClear(renderer);

    while (SDL_PollEvent(&e) != 0) {
      switch (e.type) {
        case SDL_QUIT:
            return false;
        case SDL_MOUSEBUTTONDOWN:
            if (optionsButton.InBounds(e.button.x, e.button.y)) {
              //startButton.Click();
              optionsButton.Click();
            }
        }
    }

    startButton.Render(renderer);
    optionsButton.Render(renderer);
    exitButton.Render(renderer);
    SDL_RenderPresent(renderer);
    return true;
}

int main() {
  if (init() != 0) {
      return 1;
  }


    while (loop()) {
        SDL_Delay(1000/60);
    };
    destroy();
    return 0;
}
