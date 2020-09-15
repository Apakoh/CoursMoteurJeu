#include "TP1.h"
#include <iostream>
#include <glm/glm.hpp>
#include <sfml/graphics.hpp>
#include <sfml/graphics/image.hpp>

int foo()
{
        glm::vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);
        glm::mat4 Model = glm::mat4(1.0);
        Model[4] = glm::vec4(1.0, 1.0, 0.0, 1.0);
        glm::vec4 Transformed = Model * Position;
        return 0;
}

int main()
{
  CreateImage();
  return 0;
}

void CreateImage()
{
  sf::RenderWindow window(sf::VideoMode(800, 800), "Main Window");
    sf::CircleShape shape(300.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}

void IntersectionRayonSphere()
{
  /*vpc = c - p  // this is the vector from p to c

if ((vpc . d) < 0) // when the sphere is behind the origin p
                    // note that this case may be dismissed if it is
                    // considered that p is outside the sphere
        if (|vpc| > r)

                   // there is no intersection

	else if (|vpc| == r)

		intersection = p

	else // occurs when p is inside the sphere

		pc = projection of c on the line
                // distance from pc to i1
		dist = sqrt(radius^2 - |pc - c|^2)
		di1 = dist - |pc - p|
		intersection = p + d * di1

else // center of sphere projects on the ray

	pc = projection of c on the line
	if (| c - pc | > r)

		// there is no intersection

	else
                // distance from pc to i1
		dist = sqrt(radius^2 - |pc - c|^2)

      		if (|vpc| > r) // origin is outside sphere

			di1 = |pc - p| - dist

		else // origin is inside sphere

			di1 = |pc - p| + dist

		intersection = p + d * di1*/
}
