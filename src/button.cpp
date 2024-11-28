#include <string>
#include <functional>
#include "../include/util.h"
#include <SDL_ttf.h>
#include <SDL.h>

Point CENTER = getScreenCenter(640,480);
//Should work like in the browser, where we get the object, text and onClick
//function tied to it.
//For rendering puprose we also need dimensions and color to fill the rect.
class Button {
  private:
    std::string text;
    std::function<void()> onClick;
    std::array<int, 4> backgroundColor = {};
    std::array<Uint8, 3> foregroundColor = {};
    std::string font = "/usr/share/fonts/TTF/Comic.TTF";
    int fontSize = 24;
    SDL_Surface* surface;
    SDL_Texture* texture;
    int width = 0;
    int height = 0;
    int x = 0;
    int y = 0;
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

Button::Button(std::string text, std::function<void()> onClickFun) {
  this->text = text;
  this->onClick = onClickFun;
}

Button::Button(std::string text) {
  this->text = text;
  this->onClick = NULL;
}

void Button::Click() {
  this->onClick();
}

Point Button::GetSize() {
  Point size = {width, height};
  return size;
}

bool Button::InBounds(int x, int y) {
  int result = 0;
  if (x >= this->x && x <= this->x + width) {
    result += 1;
  }
  if (y >= this->y && y <= this->y + height) {
    result += 1;
  }
  return result == 2;
}

void Button::ChangeText(std::string newText) {
  this->text = newText;
}

void Button::ChangeEvent(std::function<void()> newFun) {
  this->onClick = newFun;
}

void Button::operator=(Button& button) {
  this->text = button.text;  
  this->onClick = button.onClick;
}
void Button::SetSize(int width, int height) {
  this->width = width;
  this->height = height;
}

void Button::SetPoint(int x, int y) {
  this->x = x;
  this->y = y;
}

void Button::SetBackgroundColor(int red, int green, int blue, int alpha) {
  backgroundColor = {red, green, blue, alpha};
}

void Button::SetBackgroundColor(int red, int green, int blue) {
  backgroundColor = {red, green, blue, 255};
}

void Button::SetForegroundColor(int red, int green, int blue) {
  foregroundColor = {(Uint8) red, (Uint8) green, (Uint8) blue};
}

int Button::RenderButton(SDL_Renderer* renderer) {
  SDL_Rect box;
  box.w = this->width;
  box.h = this->height;
  box.x = this->x;
  box.y = this->y;
  if (SDL_RenderFillRect(renderer, &box) != 0) {
    SDL_GetError();
  };
  return 0;
}

//TODO: see if the drawing color needs to be reset after rendering 
int Button::Render(SDL_Renderer* renderer) {
  TTF_Font* Sans = TTF_OpenFont(font.c_str(), fontSize);
  SDL_Color textColor = {foregroundColor[0], foregroundColor[1], foregroundColor[2], 255};
  surface = TTF_RenderText_Solid(Sans, text.c_str(), textColor);

  texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_Rect Button_rect;
  Button_rect.h = pointToPixel(24) * 2.5;
  Button_rect.w = pointToPixel(24) * 2.5;
  Button_rect.x = CENTER.x + Button_rect.w/2;
  Button_rect.y = y;

  if (Button_rect.h > height || Button_rect.w > width) {
    SDL_LogError(1, "Text size is bigger than box size");
    return 1;
  }

  SDL_SetRenderDrawColor(renderer, 0x18, 0x18, 0x18, 0xff); 
  SDL_RenderFillRect(renderer, &Button_rect);
  SDL_RenderCopy(renderer, texture, NULL, &Button_rect);
  SDL_SetRenderDrawColor(renderer, 255,255,255,255);
  TTF_CloseFont(Sans);
  return 0;
}

//Free surface and texture after rendering with text
Button::~Button() {
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}
