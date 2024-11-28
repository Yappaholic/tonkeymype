#ifndef BUTTON
#define BUTTON
#include <string>
#include <SDL.h>
#include <array>
#include <functional>
#include "../include/util.h"

class Button {
  private:
    std::string text;
    std::function<void()> onClick;
    std::array<int, 4> backgroundColor = {};
    std::array<int, 3> foregroundColor = {};
    std::string font;
    int fontSize;
    SDL_Surface* surface;
    SDL_Texture* texture;
    int width = 0;
    int height = 0;
  public:
    Button(std::string text, std::function<void()> onClickFun);
    Button(std::string text);
    ~Button();
    void operator=(Button& button);
    void Click();
    bool InBounds(int x, int y);
    void ChangeText(std::string newText);
    void ChangeEvent(std::function<void()> newFun);
    void SetBackgroundColor(int red, int green, int blue, int alpha);
    void SetBackgroundColor(int red, int green, int blue);
    void SetForegroundColor(int red, int green, int blue);
    void SetSize(int width, int height);
    Point GetSize();
    void SetPoint(int x, int y);
    int Render(SDL_Renderer* renderer);
    int RenderButton(SDL_Renderer* renderer);
};
#endif
