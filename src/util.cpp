#include <SDL.h>
struct Point {
  int x;
  int y;
};

struct DPI {
  float diagonal;
  float horizontal;
  float vertical;
};

Point getScreenCenter(int width, int height) {
    int centerX = (width/2) - 50;
    int centerY = (height/2) - 50;
    Point result = {centerX, centerY};
    return result;
};

DPI getScreenDPI() {
  float ddpi,hdpi,vdpi;
  DPI dpi;
  if (SDL_GetDisplayDPI(0, &ddpi, &hdpi, &vdpi) == 0) {
    dpi = {ddpi, hdpi, vdpi};
  } else {
    dpi = {NULL, NULL, NULL};
  }
  return dpi;
}

int pointToPixel(int points) {
  int pixels = (96/72) * points;
  return pixels;
}
