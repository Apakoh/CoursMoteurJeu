#include <glm/glm.hpp>

class Ray
{
  public:
    glm::vec3 origin;
    glm::vec3 direction;

  Ray(glm::vec3 _origin, glm::vec3 _direction)
  {
    origin = _origin;
    direction = _direction;
  }
};
