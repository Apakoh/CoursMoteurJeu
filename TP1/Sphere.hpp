#include <glm/gtx/intersect.hpp>

class Sphere
{
  public:
    float radius;
    glm::vec3 center;
    glm::vec3 color;

    Sphere(glm::vec3 _center, float _radius, glm::vec3 _color)
    {
      radius = _radius;
      center = _center;
      color = _color;
    }

    Sphere()
    {
      
    }
};
