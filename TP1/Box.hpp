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

  Box UnionBox(Box b1, Box b2)
  {
    float a_x, a_y, a_z;
    float b_x, b_y, b_z;

    glm::vec3 _a, _b;

    // Calcul of a
    if(b1.a.x > b2.a.x)
      a_x = b1.a.x;
    else
      a_x = b2.a.x;
    if(b1.a.y > b2.a.y)
      a_y = b1.a.y;
    else
      a_y = b2.a.y;
    if(b1.a.z > b2.a.z)
      a_z = b1.a.z;
    else
      a_z = b2.a.z;

    // Calcul of b
    if(b1.b.x > b2.b.x)
      b_x = b1.b.x;
    else
      b_x = b2.b.x;
    if(b1.b.y > b2.b.y)
      b_y = b1.b.y;
    else
      b_y = b2.b.y;
    if(b1.b.z > b2.b.z)
      b_z = b1.b.z;
    else
      b_z = b2.b.z;

    _a = glm::vec3(a_x, a_y, a_z);
    _b = glm::vec3(b_x, b_y, b_z);

    return Box(_a, _b);
  }

};
