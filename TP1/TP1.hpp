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

class Pixel
{
  public:
    Ray r;
    int x;
    int y;
};

class Scene
{
  public:
    Camera camera;
    Light light;
};

void CreateWindow(Camera c);
void SetPixelCamera(sf::Image& img, int x, int y, glm::vec3 color);
void IntersectObject(Sphere s, Light l, Pixel px, sf::Image& img);
void IntersectObjects(Sphere *spheres, Light l, Pixel px, sf::Image& img);
void RayCastCamera(Sphere *spheres, Light l, Pixel px, sf::Image& img);
