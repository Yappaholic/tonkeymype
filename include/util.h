#ifndef UTIL
#define UTIL
struct Point {
  int x;
  int y;
};
Point getScreenCenter(int width, int height);
int pointToPixel(int points);
#endif
