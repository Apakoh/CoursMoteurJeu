#include "TP1.hpp"
#include <iostream>
#include <glm/gtx/intersect.hpp>
#include <sfml/graphics.hpp>
#include <sfml/graphics/image.hpp>

int main()
{
  unsigned int height = 800;
  unsigned int width = 800;
  Ray r;
  glm::vec3 out;

  Sphere s;
  s.center = glm::vec3(width/2, height/2, 0);
  s.radius = 100.0;
  sf::RenderWindow window(sf::VideoMode(width, height), "Main Window");

  sf::Image img;
  img.create(width, height);

  for(int x = 0; x < width; x++)
  {
    for(int y = 0; y < height; y++)
    {
      r.origin = glm::vec3(x, y, 0);
      r.direction = glm::vec3(0,0,1);
      if(glm::intersectRaySphere(r.origin, r.direction, s.center, s.radius, out, out))
      {
        img.setPixel(x, y, sf::Color(255,255,255));
      }
      else
      {
        img.setPixel(x, y, sf::Color(0,0,0));
      }
    }
  }

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
  return 0;
}
