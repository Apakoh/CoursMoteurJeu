#include "Ray.cpp"

class Pixel
{
  public:
    Ray* r;
    int x;
    int y;

  Pixel(Ray* _r,  int _x, int _y)
  {
    r = _r;
    x = _x;
    y = _y;
  }
};
