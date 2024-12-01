#ifndef APP
#define APP
#include <SDL.h>
#include "../include/button.h"
enum State {
  MAIN_MENU,
  PAUSE_MENU,
  RUNNING
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
    void HandleEvents();
    int Error();
    void Draw();
    bool Running();
    void Quit();
};
#endif
