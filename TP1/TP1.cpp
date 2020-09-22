#include "TP1.hpp"
#include <iostream>
#include <glm/gtx/intersect.hpp>
#include <sfml/graphics.hpp>
#include <sfml/graphics/image.hpp>
#include <math.h>

int main()
{
  sf::Image img;
  Camera c;

  c.height = 800;
  c.width = 800;
  c.img = img;

  c.img.create(c.width, c.height);

  Ray r;

  Sphere s;
  s.center = glm::vec3(c.width/2, c.height/2, 0);
  s.radius = 100.0;
  s.color = glm::vec3(255, 255, 255);

  //Light
  Light l;
  l.position = glm::vec3(100, 100, 400);
  l.l_e = glm::vec3(1000, 0, 1000);

  glm::vec3 intersection_position;
  glm::vec3 intersection_normal;

  for(int x = 0; x < c.width; x++)
  {
    for(int y = 0; y < c.height; y++)
    {
      r.origin = glm::vec3(x, y, 0);
      r.direction = glm::vec3(0,0,1);

      IntersectObject(s, r, l, x, y, c.img);
    }
  }

  // 0 ------------> x
  // |
  // |
  // |
  // V
  // y

  CreateWindow(c);

  return 0;
}


void SetPixelCamera(sf::Image& img, int x, int y, glm::vec3 c)
{
  img.setPixel(x, y, sf::Color(c.x, c.y, c.z));
}

void IntersectObjects(glm::vec3 lamp, Sphere *spheres, Ray r)
{
  for(int i = 0; i < sizeof(spheres); i++)
  {

  }
}

void IntersectObject(Sphere s, Ray r, Light l, int x, int y, sf::Image& img)
{
  glm::vec3 intersection_position;
  glm::vec3 intersection_normal;

  if(glm::intersectRaySphere(r.origin, r.direction, s.center, s.radius, intersection_position, intersection_normal))
  {
    glm::vec3 lamp_direction = l.position - intersection_position;
    if(!glm::intersectRaySphere(intersection_position, lamp_direction, s.center, s.radius, intersection_position, intersection_normal))
    {
      // Calcul of D
      float distance_carre = lamp_direction.x * lamp_direction.x  + lamp_direction.y * lamp_direction.y  + lamp_direction.z * lamp_direction.z;

      // Calcul for color
      glm::vec3 l_e_and_object_color = (l.l_e * s.color);
      l_e_and_object_color = glm::vec3(l_e_and_object_color.x/255, l_e_and_object_color.y/255, l_e_and_object_color.z/255);

      glm::vec3 lamp_to_intersect = glm::normalize(lamp_direction) * glm::normalize(lamp_direction);

      // Calcul for cos theta
      float cos_theta = glm::abs(glm::dot(glm::normalize(r.direction),glm::normalize(lamp_direction)));

      // Final Fantasy Calcul : A Real Reborn XII
      glm::vec3 color_temp = l.l_e * lamp_to_intersect * (cos_theta / (float)M_PI);
      sf::Color color = sf::Color(color_temp.x, color_temp.y, color_temp.z);

      SetPixelCamera(img, x, y, color_temp);
    }
    else
    {
      img.setPixel(x, y, sf::Color(s.color.x, s.color.y, s.color.z));
    }
  }
  else
  {
    img.setPixel(x, y, sf::Color(0,0,0));
  }
}

void CreateWindow(Camera c)
{

  sf::RenderWindow window(sf::VideoMode(c.width, c.height), "Main Window");

  sf::Texture texture;
  texture.loadFromImage(c.img);

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
