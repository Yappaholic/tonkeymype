#include <iostream>
#include <SDL.h>
#include "../include/button.h"
#include <SDL_ttf.h>

using namespace std;
int FPS = 60;
SDL_Window *window;
SDL_Renderer* renderer;

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

    int result = SDL_CreateWindowAndRenderer(640,480, NULL, &window, &renderer);
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
  std::cout << "Hello,world!";
}

bool loop() {
    SDL_Event e;
    Button startButton("Start", sayHello);
    startButton.SetForegroundColor(255,255,255);
    startButton.SetDimensions(50, 50);

    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 120);
    //SDL_RenderClear(renderer);

    while (SDL_PollEvent(&e) != 0) {
      switch (e.type) {
        case SDL_QUIT:
            return false;
        }
    }

    startButton.Render(renderer);
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
