#include <glm/glm.hpp>
#include <sfml/graphics.hpp>
#include <sfml/graphics/image.hpp>

class Sphere
{
  public:
    float radius;
    glm::vec3 center;
};

class Ray
{
  public:
    glm::vec3 origin;
    glm::vec3 direction;
};

void CreateWindow(sf::Image img);
