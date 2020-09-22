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

void CreateWindow(sf::Image img);
void IntersectObject(Sphere s, Ray r, glm::vec3 lamp);
void SetPixelCamera(sf::Image img, int x, int y, glm::vec3 color);
