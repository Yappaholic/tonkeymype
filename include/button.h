#ifndef BUTTON
#define BUTTON
#include <string>
#include <SDL.h>
#include <array>
#include <functional>

class Button {
  private:
    std::string text;
    std::function<void()> onClick;
    std::array<int, 4> backgroundColor = {};
    std::array<int, 3> foregroundColor = {};
    SDL_Surface* surface;
    SDL_Texture* texture;
    int width = 0;
    int height = 0;
  public:
    Button(std::string textInit, std::function<void()> onClickFun);
    ~Button();
    void operator=(Button& button);
    void Click();
    void ChangeText(std::string newText);
    void ChangeEvent(std::function<void()> newFun);
    void SetBackgroundColor(int red, int green, int blue, int alpha);
    void SetBackgroundColor(int red, int green, int blue);
    void SetForegroundColor(int red, int green, int blue);
    void SetDimensions(int width, int height);
    void Render(SDL_Renderer* renderer);
};
#endif
