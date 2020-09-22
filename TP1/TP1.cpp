#include "TP1.hpp"
#include <iostream>
#include <glm/gtx/intersect.hpp>
#include <sfml/graphics.hpp>
#include <sfml/graphics/image.hpp>
#include <math.h>

int main()
{
  unsigned int height = 800;
  unsigned int width = 800;
  Ray r;
  glm::vec3 intersection_position;
  glm::vec3 intersection_normal;


  Sphere s;
  s.center = glm::vec3(width/2, height/2, 0);
  s.radius = 100.0;

  //Light
  glm::vec3 lamp = glm::vec3(100, 100, 100);
  glm::vec3 l_e = glm::vec3(255, 0, 0);

  glm::vec3 sphere_color = glm::vec3(255, 255, 255);


  sf::Image img;
  img.create(width, height);

  for(int x = 0; x < width; x++)
  {
    for(int y = 0; y < height; y++)
    {
      r.origin = glm::vec3(x, y, 0);
      r.direction = glm::vec3(0,0,1);

      if(glm::intersectRaySphere(r.origin, r.direction, s.center, s.radius, intersection_position, intersection_normal))
      {
        glm::vec3 lamp_direction = lamp - intersection_position;
        if(!glm::intersectRaySphere(intersection_position, lamp_direction, s.center, s.radius, intersection_position, intersection_normal))
        {
          // Calcul of D
          float distance_carre = lamp_direction.x * lamp_direction.x  + lamp_direction.y * lamp_direction.y  + lamp_direction.z * lamp_direction.z;
          //std::cout << distance_carre << std::endl;

          // Calcul for color
          // glm::vec3 l_e_and_object_color = (l_e * sphere_color);
          // l_e_and_object_color = glm::vec3(l_e_and_object_color.x/255, l_e_and_object_color.y/255, l_e_and_object_color.z/255);

          glm::vec3 lamp_to_intersect = glm::normalize(lamp_direction) * glm::normalize(lamp_direction);

          // Calcul for cos theta
          float cos_theta = glm::abs(glm::dot(glm::normalize(r.direction),glm::normalize(lamp_direction)));
          //std::cout << cos_theta << std::endl;

          // Final Fantasy Calcul : A Real Reborn XII
          glm::vec3 color_temp = sphere_color * lamp_to_intersect * (cos_theta / (float)M_PI);
          sf::Color color = sf::Color(color_temp.x, color_temp.y, color_temp.z);
          img.setPixel(x, y, color);
          img.setPixel(x, y, sf::Color(0, 255, 255));
        }
        else
        {
          img.setPixel(x, y, sf::Color(sphere_color.x, sphere_color.y, sphere_color.z));
        }
      }
      else
      {
        img.setPixel(x, y, sf::Color(0,0,0));
      }
    }
  }

  // 0 ------------> x
  // |
  // |
  // |
  // V
  // y

  CreateWindow(img);

  return 0;
}

void CreateWindow(sf::Image img)
{
  unsigned int height = 800;
  unsigned int width = 800;

  sf::RenderWindow window(sf::VideoMode(width, height), "Main Window");

  sf::Texture texture;
  texture.loadFromImage(img);

  sf::Sprite sprite;
  sprite.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
}
