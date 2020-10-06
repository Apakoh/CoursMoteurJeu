#include <glm/glm.hpp>

class Light
{
  public:
    glm::vec3 position;
    glm::vec3 l_e;

  Light(glm::vec3 _position, glm::vec3 _l_e)
  {
    position = _position;
    l_e = _l_e;
  }
};
