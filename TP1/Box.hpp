#include <glm/gtx/intersect.hpp>
#include "TP1.hpp"
#include "Vector3.cpp"

class Box
{

public:
  glm::vec3 a;
	glm::vec3 b;

  Box(Sphere* s)
  {
    BoxSphere(s);
  }

  Box(glm::vec3 _a, glm::vec3 _b)
  {
    a = _a;
    b = _b;
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

  Box UnionBox(Box* _b1, Box* _b2)
  {
    glm::vec3 _a, _b;

    _a = Vec3Min(_b1->a, _b2->a);
    _b = Vec3Min(_b1->b, _b2->b);

    return Box(_a, _b);
  }

};

void IntersectionRayBox();
