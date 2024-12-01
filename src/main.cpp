#include <iostream>
#include <SDL.h>
#include "../include/button.h"
#include "../include/util.h"
#include <SDL_ttf.h>
#include "../include/app.h"

using namespace std;
SDL_Window *window;
SDL_Renderer* renderer;
extern MainSettings settings;
Point screenCenter = getScreenCenter(settings.SCREEN_WIDTH, settings.SCREEN_HEIGHT);

void sayHello() {
  SDL_Log("Hello, world!");
}

void game_loop() {
  SDL_SetRenderDrawColor(renderer,255,255,255,255);
  Button newButton("New", sayHello);
  newButton.SetForegroundColor(255,255,255);
  newButton.SetSize(100,100);
  newButton.SetPoint(320, 240);
  while(true) {
    newButton.Render(renderer);
  }
}


int main() {
  App app;
  if (app.Init() != 0) {
      return 1;
  }
  app.MainMenu();


  while (app.Running() == true) {
    app.HandleEvents();
    app.Draw();

    SDL_Delay(1000/settings.FPS);
  };
  app.Quit();
  return 0;
}
