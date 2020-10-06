#include <glm/gtx/intersect.hpp>
#include "TP1.hpp"

class Box
{

public:
  glm::vec3 a;
	glm::vec3 b;

  Box(Sphere* s)
  {
    BoxSphere(s);
  }

	void BoxSphere(Sphere* s)
	{
    float a_x = s->center.x - s->radius;
    float a_y = s->center.y - s->radius;
    float a_z = s->center.z - s->radius;

    float b_x = s->center.x + s->radius;
    float b_y = s->center.y + s->radius;
    float b_z = s->center.z + s->radius;


    a = glm::vec3(a_x, a_y, a_z);
    b = glm::vec3(b_x, b_y, b_z);
	}

  void BoxTriangle() {}

  void UnionBox(Box b1, Box b2)
  {
    float a_x, a_y, a_z;
    float b_x, b_y, b_z;
  }

};
