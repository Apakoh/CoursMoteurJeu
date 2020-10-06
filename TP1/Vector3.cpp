#include "Vector3.hpp"

glm::vec3 Vec3Min(glm::vec3 _a, glm::vec3 _b)
{
  float vec_x, vec_y, vec_z;
  glm::vec3 _vec_min;

  if(_a.x > _b.x)
    vec_x = _a.x;
  else
    vec_x = _b.x;
  if(_a.y > _b.y)
    vec_y = _a.y;
  else
    vec_y = _b.y;
  if(_a.z > _b.z)
    vec_z = _a.z;
  else
    vec_z = _b.z;

  _vec_min = glm::vec3(vec_x, vec_y, vec_z);

  return _vec_min;
}
