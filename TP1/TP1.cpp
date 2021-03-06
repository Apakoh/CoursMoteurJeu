#include "TP1.hpp"
#include <iostream>
#include <glm/gtx/intersect.hpp>
#include <sfml/graphics.hpp>
#include <math.h>


  // Grid :
  // 0 ------------> x
  // |
  // |
  // |
  // V
  // y

const int color_clamp = 255;

const glm::vec3 color_bg = glm::vec3(0, 0, 0);

int main()
{
  sf::Image img;
  Camera c = Camera(800, 800, &img);

  c.img->create(c.width, c.height);

  Scene main_scene = Scene(&c);

  // Spheres : Center / Radius / Albedo (color)
  Sphere s1 = Sphere(glm::vec3(400, 400, 900), 100.0, glm::vec3(255, 255, 255));
  Sphere s2 = Sphere(glm::vec3(100, 100, 100), 200.0, glm::vec3(255, 0, 0));
  Sphere s3 = Sphere(glm::vec3(600, 600, 400), 100.0, glm::vec3(0, 177, 100));

  main_scene.AddSphere(s1);
  main_scene.AddSphere(s3);

  //Lights : Center / Light Power + color
  Light l1 = Light(glm::vec3(100, 800, -650), glm::vec3(1000, 1000, 1000));
  Light l2 = Light(glm::vec3(0, 0, 0), glm::vec3(800, 0, 0));
  Light l3 = Light(glm::vec3(800, 0, 0), glm::vec3(0, 0, 800));

  main_scene.AddLight(l1);
  main_scene.AddLight(l2);
  main_scene.AddLight(l3);

  std::cout << main_scene.lights[0].position.x << std::endl;
  std::cout << main_scene.spheres[0].radius  << std::endl;

  RayCastCamera(&main_scene);
  CreateWindow(c);

  return 0;
}

void RayCastCamera(Scene* _scene)
{
  for(int x = 0; x < _scene->camera->width; x++)
  {
    for(int y = 0; y < _scene->camera->height; y++)
    {
      // Ray : Coordinates of the Pixel / Direction of the Ray
      Ray r = Ray(glm::vec3(x, y, 0), glm::vec3(0,0,1));

      Pixel px = Pixel(&r, x, y);

      LightsToObjects(_scene, &px);
    }
  }
}

void SetPixelCamera(sf::Image* img, int x, int y, glm::vec3 c)
{
  img->setPixel(x, y, sf::Color(c.x, c.y, c.z));
}

void LightsToObjects(Scene* _scene, Pixel* px)
{
  glm::vec3 color = glm::vec3(0,0,0);
  glm::vec3 intersection;
  glm::vec3 normal;

  Sphere s;

  if(!ShortestIntersection(_scene, px, intersection, normal, s))
  {
    return;
  }

  IntersectObjects(s, _scene, px, intersection, normal, color);

  color = glm::clamp(color, glm::vec3(0, 0, 0), glm::vec3(color_clamp, color_clamp, color_clamp));

  SetPixelCamera(_scene->camera->img, px->x, px->y, color);
}

void IntersectObjects(Sphere& s, Scene* _scene, Pixel* px, glm::vec3& intersect, glm::vec3& normal, glm::vec3& color)
{
  glm::vec3 intersection_normal;
  glm::vec3 intersection_position_sphere_light;
  glm::vec3 lamp_direction;

  bool path_to_light;

  for(int i = 0; i < _scene->nb_light; i++)
  {
    lamp_direction = glm::normalize(_scene->lights[i].position - intersect);
    path_to_light = true;

    // Sphere to Lamp
    for(int j = 0; j < _scene->nb_sphere; j++)
    {
        if(RaySphereIntersect(intersect, lamp_direction, _scene->spheres[j].center, _scene->spheres[j].radius, intersection_position_sphere_light, intersection_normal))
        {
          path_to_light = false;
          break;
        }
    }

    if(path_to_light)
    {
      // Calculate color for
      LightOnFireTanana(s, _scene->lights[i], px, color, intersect, normal, lamp_direction);
    }
  }
}

// https://www.youtube.com/watch?v=aTBlKRzNf74
void LightOnFireTanana(Sphere s, Light l, Pixel* px, glm::vec3& color, glm::vec3& intersection_position, glm::vec3& normal, glm::vec3& lamp_direction)
{
    // Calcul of D
    float x = (intersection_position.x - l.position.x);
    float y = (intersection_position.y - l.position.y);
    float z = (intersection_position.z - l.position.z);
    float distance_carre = x * x + y * y + z * z;

    // Normal of lamp_direction
    float lamp_to_intersect = glm::abs(glm::dot(normal, lamp_direction));

    // l.l_e / d²
    glm::vec3 le = glm::vec3(l.l_e.x * l.l_e.x / distance_carre, l.l_e.y * l.l_e.y / distance_carre, l.l_e.z * l.l_e.z / distance_carre);

    // Light vector
    glm::vec3 light_vector = glm::normalize(intersection_position - l.position);
    // Calcul for angle
    float angle = glm::dot(normal, -light_vector);

    // Final Fantasy Calcul : A Real Reborn XII
    //color += le * (angle / (float)M_PI) * lamp_to_intersect * s.color;

    if(angle <= 0)
    {
      color = color_bg;
    }
    else
    {
          color += s.color * le * angle;
    }
}

void CreateWindow(Camera c)
{
  sf::RenderWindow window(sf::VideoMode(c.width, c.height), "Main Window");

  sf::Texture texture;
  texture.loadFromImage(*c.img);

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
            else if (event.type == sf::Event::Resized)
            {
              //window.setSize({ static_cast<float>(event.size.width),static_cast<float>(event.size.height) });
            }
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
}

bool ShortestIntersection(Scene* _scene, Pixel* px, glm::vec3& intersection, glm::vec3& normal, Sphere& sph)
{
  glm::vec3 intersection_position;
  glm::vec3 intersection_normal;

  int indice = 0;
  float distance = 0;
  float distance_temp;

  bool intersect = false;

  for(int i = 0; i < _scene->nb_sphere; i++)
  {
    if(RaySphereIntersect(px->r->origin, px->r->direction, _scene->spheres[i].center, _scene->spheres[i].radius, intersection_position, intersection_normal))
    {
      distance_temp = glm::distance(intersection_position, px->r->origin);
      if(distance_temp < distance && distance > 0);
      {
          intersect = true;
          intersection = intersection_position;
          normal = intersection_normal;
          distance = distance_temp;
          indice = i;
      }
    }
  }

  sph = _scene->spheres[indice];
  return intersect;
}
