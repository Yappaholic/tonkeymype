#include <iostream>
#include <SDL.h>

using namespace std;
int main() {
  SDL_Surface *winSurface = NULL;
  SDL_Window *window = NULL;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
      goto Error;
  }

  window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
  if (!window) {
     goto Error;
  }

  winSurface = SDL_GetWindowSurface(window);
  if (!winSurface) {
      goto Error;
  }
  SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 255, 255, 255));
  SDL_UpdateWindowSurface(window);
  system("pause");

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;

Error:
      cout << "Error initializing" << SDL_GetError() << endl;
      system("pause");
      return 1;;
}
