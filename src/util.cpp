struct Point {
  int x;
  int y;
};

Point getScreenCenter(int width, int height) {
    int centerX = (width/2) - 50;
    int centerY = (height/2) - 50;
    Point result = {centerX, centerY};
    return result;
};
