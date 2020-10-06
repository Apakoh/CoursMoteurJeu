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

const int nb_spheres = 2;
const int nb_lights = 3;

const int color_clamp = 255;

const glm::vec3 color_bg = glm::vec3(147, 200, 180);

int main()
{
  sf::Image img;
  Camera c = Camera(800, 800, &img);

  c.img->create(c.width, c.height);

  Sphere s1 = Sphere(glm::vec3(400, 400, 900), 400.0, glm::vec3(255, 255, 255));
  Sphere s2 = Sphere(glm::vec3(100, 100, 100), 200.0, glm::vec3(255, 0, 0));
  Sphere s3 = Sphere(glm::vec3(600, 600, 400), 400.0, glm::vec3(0, 177, 100));

  Sphere spheres[nb_spheres] = {s1, s3};

  //Light
  Light l1 = Light(glm::vec3(100, 800, -650), glm::vec3(1000, 1000, 1000));
  Light l2 = Light(glm::vec3(0, 0, 0), glm::vec3(800, 0, 0));
  Light l3 = Light(glm::vec3(800, 0, 0), glm::vec3(0, 0, 800));

  Light lights[nb_lights] = {l1, l2, l3};

  Scene main_scene = Scene(&c, lights, spheres);

  RayCastCamera(c, spheres, lights, *c.img);
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

      LightsToObjects(spheres, l, px, *c.img);
    }
  }
}

void SetPixelCamera(sf::Image& img, int x, int y, glm::vec3 c)
{
  img.setPixel(x, y, sf::Color(c.x, c.y, c.z));
}

void LightsToObjects(Sphere *spheres, Light *l, Pixel px, sf::Image& img)
{
  glm::vec3 color = glm::vec3(0,0,0);
  glm::vec3 intersection;
  glm::vec3 normal;

  Sphere s;

  if(!ShortestIntersection(spheres, px, intersection, normal, s))
  {
    return;
  }

  IntersectObjects(s, l, px, intersection, normal, color, spheres);

  color = glm::clamp(color, glm::vec3(0, 0, 0), glm::vec3(color_clamp, color_clamp, color_clamp));

  SetPixelCamera(img, px.x, px.y, color);
}

void IntersectObjects(Sphere s, Light *l, Pixel px, glm::vec3& intersect, glm::vec3& normal, glm::vec3& color, Sphere *spheres)
{
  glm::vec3 intersection_normal;
  glm::vec3 intersection_position_sphere_light;
  glm::vec3 lamp_direction;

  bool path_to_light;

  for(int i = 0; i < nb_lights; i++)
  {
    lamp_direction = glm::normalize(l[i].position - intersect);
    path_to_light = true;

    // Sphere to Lamp
    for(int j = 0; j < nb_spheres; j++)
    {
        if(RaySphereIntersect(intersect, lamp_direction, spheres[j].center, spheres[j].radius, intersection_position_sphere_light, intersection_normal))
        {
          path_to_light = false;
          break;
        }
    }

    if(path_to_light)
    {
      // Calculate color for
      LightOnFireTanana(s, l[i], px, color, intersect, normal, lamp_direction);
    }
  }
}

// https://www.youtube.com/watch?v=aTBlKRzNf74
void LightOnFireTanana(Sphere s, Light l, Pixel px, glm::vec3& color, glm::vec3& intersection_position, glm::vec3& normal, glm::vec3& lamp_direction)
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

bool ShortestIntersection(Sphere *spheres, Pixel px, glm::vec3& intersection, glm::vec3& normal, Sphere& sph)
{
  glm::vec3 intersection_position;
  glm::vec3 intersection_normal;

  int indice = 0;
  float distance = 0;
  float distance_temp;

  bool intersect = false;

  for(int i = 0; i < nb_spheres; i++)
  {
    if(RaySphereIntersect(px.r.origin, px.r.direction, spheres[i].center, spheres[i].radius, intersection_position, intersection_normal))
    {
      distance_temp = glm::distance(intersection_position, px.r.origin);
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

  sph = spheres[indice];
  return intersect;
}

bool RaySphereIntersect(glm::vec3 &r_origin, glm::vec3 &r_direction, glm::vec3 &sphere_center, float sphere_radius, glm::vec3 &position, glm::vec3 &normal)
{
    float t0, t1, t;

    sphere_radius *= 100;
    glm::vec3 ray_sphere_direction = sphere_center - r_origin;
    float tca = glm::dot(ray_sphere_direction, r_direction);

    if (tca < 0) {
        return false;
    }

    float d2 = glm::dot(ray_sphere_direction, ray_sphere_direction) - tca * tca;

    if (d2 > sphere_radius) {
        return false;
    }

    float thc = sqrt(sphere_radius - d2);

    t0 = tca - thc;
    t1 = tca + thc;

    if (t0 > t1) {
        std::swap(t0, t1);
    }

    if (t0 < 0) {
        t0 = t1;
        if (t0 < 0) {
            return false;
        }
    }

    t = t0;

    position = r_origin + t * r_direction;
    normal = glm::normalize(position - sphere_center);

    return true;
}
