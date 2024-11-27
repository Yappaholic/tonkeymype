#include <string>
#include <functional>
#include <SDL_ttf.h>
#include <SDL.h>

//Should work like in the browser, where we get the object, text and onClick
//function tied to it.
//For rendering puprose we also need dimensions and color to fill the rect.
class Button {
  private:
    std::string text;
    std::function<void()> onClick;
    std::array<int, 4> backgroundColor = {};
    std::array<Uint8, 3> foregroundColor = {};
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

Button::Button(std::string textInit, std::function<void()> onClickFun) {
  text = textInit;
  onClick = onClickFun;
}


void Button::Click() {
  onClick();
}

void Button::ChangeText(std::string newText) {
  text = newText;
}

void Button::ChangeEvent(std::function<void()> newFun) {
  onClick = newFun;
}

void Button::operator=(Button& button) {
  text = button.text;  
  onClick = button.onClick;
}
void Button::SetDimensions(int width, int height) {
  this->width = width;
  this->height = height;
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

void Button::Render(SDL_Renderer* renderer) {
  TTF_Font* Sans = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 16);
  SDL_Color textColor = {foregroundColor[0], foregroundColor[1], foregroundColor[2], 255};
  surface = TTF_RenderText_Solid(Sans, text.c_str(), textColor);

  texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_Rect Button_rect;
  Button_rect.h = height;
  Button_rect.w = width;
  Button_rect.x = 100;
  Button_rect.y = 100;
  SDL_SetRenderDrawColor(renderer, 0x18, 0x18, 0x18, 0xff); 
  SDL_RenderFillRect(renderer, &Button_rect);
  SDL_RenderCopy(renderer, texture, NULL, &Button_rect);
  TTF_CloseFont(Sans);
}

Button::~Button() {
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}
