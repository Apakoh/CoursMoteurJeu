#include "TP1.hpp"
#include <iostream>
#include <glm/gtx/intersect.hpp>
#include <sfml/graphics.hpp>
#include <sfml/graphics/image.hpp>
#include <math.h>


  // Grid :
  // 0 ------------> x
  // |
  // |
  // |
  // V
  // y

const int nb_spheres = 2;
const int nb_lights = 4;

const int color_clamp = 255;

int main()
{
  sf::Image img;
  Camera c;

  c.height = 1080;
  c.width = 1920;
  c.img = img;

  c.img.create(c.width, c.height);

  Sphere s1;
  s1.center = glm::vec3(400, 400, 500);
  s1.radius = 200.0;
  s1.color = glm::vec3(255, 255, 255);
  s1.albedo = glm::vec3(1, 1, 1);

  Sphere s2;
  s2.center = glm::vec3(400, 400, 300);
  s2.radius = 100.0;
  s2.color = glm::vec3(255, 0, 0);
  s2.albedo = glm::vec3(1, 1, 1);

  Sphere s3;
  s3.center = glm::vec3(800, 800, 0);
  s3.radius = 200.0;
  s3.color = glm::vec3(0, 177, 100);
  s3.albedo = glm::vec3(1, 1, 1);

  Sphere spheres[nb_spheres] = {s1, s3};

  //Light
  Light l1;
  l1.position = glm::vec3(400, 400, -300);
  l1.l_e = glm::vec3(1000, 1000, 1000);

  Light l2;
  l2.position = glm::vec3(0, 0, -0);
  l2.l_e = glm::vec3(1000, 0, 0);

  Light l3;
  l3.position = glm::vec3(800, 0, 0);
  l3.l_e = glm::vec3(0, 0, 1000);

  Light lights[nb_lights] = {l1, l2, l3};

  Scene sc;
  sc.camera = c;
  sc.light = l1;

  RayCastCamera(c, spheres, lights, c.img);
  CreateWindow(c);

  return 0;
}

void RayCastCamera(Camera& c, Sphere *spheres, Light *l, sf::Image& img)
{
  for(int x = 0; x < c.width; x++)
  {
    for(int y = 0; y < c.height; y++)
    {
      Ray r;
      r.origin = glm::vec3(x, y, 0);
      r.direction = glm::vec3(0,0,1);

      Pixel px;
      px.r = r;
      px.x = x;
      px.y = y;

      IntersectObjects(spheres, l, px, c.img);
    }
  }
}

void SetPixelCamera(sf::Image& img, int x, int y, glm::vec3 c)
{
  img.setPixel(x, y, sf::Color(c.x, c.y, c.z));
}

void IntersectObjects(Sphere *spheres, Light *l, Pixel px, sf::Image& img)
{
  glm::vec3 color;
  glm::vec3 intersection;

  float t = 0;
  float t_temp;

  glm::vec3 color_min = glm::vec3(0,0,0);

  for(int i = 0; i < nb_spheres; i++)
  {
    if(IntersectObject(spheres[i], l, px, intersection, color))
    {
      t_temp = glm::distance(intersection, px.r.origin);
      if(t_temp < t && t > 0);
      {
          t = t_temp;
          color_min = color;
      }
    }
  }

  SetPixelCamera(img, px.x, px.y, color_min);
}

bool IntersectObject(Sphere s, Light *l, Pixel px, glm::vec3& intersect, glm::vec3& color)
{
  glm::vec3 intersection_position;
  glm::vec3 intersection_normal;

  bool path_to_light = false;

  color = glm::vec3(0,0,0);

  // Pixel to Sphere
  if(glm::intersectRaySphere(px.r.origin, px.r.direction, s.center, s.radius, intersection_position, intersection_normal))
  {
    for(int i = 0; i < nb_lights; i++)
    {
      glm::vec3 lamp_direction = l[i].position - intersection_position;
      glm::vec3 intersection_position_light;

      // Sphere to Lamp
      if(!glm::intersectRaySphere(intersection_position, lamp_direction, s.center, s.radius, intersection_position_light, intersection_normal))
      {
        // Calculate color for
        LightOnFireTanana(s, l[i], px, color, intersection_position, lamp_direction);
        intersect = intersection_position;
        path_to_light = true;
      }
    }
  }
  color = glm::clamp(color, glm::vec3(0, 0, 0), glm::vec3(color_clamp, color_clamp, color_clamp));

  return path_to_light;
}

// https://www.youtube.com/watch?v=aTBlKRzNf74
void LightOnFireTanana(Sphere s, Light l, Pixel px, glm::vec3& color, glm::vec3 intersection_position, glm::vec3 lamp_direction)
{
    // Calcul of D
    float distance_carre = lamp_direction.x * lamp_direction.x  + lamp_direction.y * lamp_direction.y  + lamp_direction.z * lamp_direction.z;

    // Normal of lamp_direction
    float lamp_to_intersect = glm::abs(glm::dot(glm::normalize(intersection_position - s.center), glm::normalize(lamp_direction)));

    // Calcul for cos theta
    //float cos_theta = glm::abs(glm::dot(glm::normalize(px.r.direction), glm::normalize(lamp_direction)));

    // Albedo
    glm::vec3 albedo = glm::normalize(s.albedo * s.color);

    // Final Fantasy Calcul : A Real Reborn XII
    color += l.l_e * lamp_to_intersect * (albedo / (float)M_PI);
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
            {
              window.close();
            }
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
}
