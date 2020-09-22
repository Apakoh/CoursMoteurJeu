#include <glm/glm.hpp>
#include <sfml/graphics.hpp>
#include <sfml/graphics/image.hpp>

class Sphere
{
  public:
    float radius;
    glm::vec3 center;
    glm::vec3 color;
};

class Ray
{
  public:
    glm::vec3 origin;
    glm::vec3 direction;
};

class Camera
{
  public:
  unsigned int height;
  unsigned int width;
  sf::Image img;
};

class Light
{
  public:
    glm::vec3 position;
    glm::vec3 l_e;
};

void CreateWindow(Camera c);
void SetPixelCamera(sf::Image& img, int x, int y, glm::vec3 color);
void IntersectObject(Sphere s, Ray r, Light l, int x, int y, sf::Image& img);
void IntersectObjects(glm::vec3 lamp, Sphere *spheres, Ray r);
