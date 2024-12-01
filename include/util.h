#ifndef UTIL
#define UTIL

struct MainSettings {
  int FPS = 60;
  int SCREEN_HEIGHT = 640;
  int SCREEN_WIDTH = 480;
};
extern MainSettings settings;
struct Point {
  int x;
  int y;
};
Point getScreenCenter(int width, int height);
int pointToPixel(int points);
#endif
