#include <sfml/graphics.hpp>

class Camera
{
  public:
  unsigned int height;
  unsigned int width;
  sf::Image* img;

  Camera(){}
  Camera(int _height, int _width, sf::Image *_img)
  {
    height = _height;
    width = _width;
    img = _img;
  }
};
