#include <glm/glm.hpp>
#include <sfml/graphics.hpp>
#include <sfml/graphics/image.hpp>

class Sphere
{
  public:
    float radius;
    glm::vec3 center;
    glm::vec3 color;
    glm::vec3 albedo;
};

class Ray
{
  public:
    glm::vec3 origin;
    glm::vec3 direction;
};

class Camera
{
  public:
  unsigned int height;
  unsigned int width;
  sf::Image img;
};

class Light
{
  public:
    glm::vec3 position;
    glm::vec3 l_e;
};

class Pixel
{
  public:
    Ray r;
    int x;
    int y;
};

class Scene
{
  public:
    Camera camera;
    Light light;
};

void CreateWindow(Camera c);
void SetPixelCamera(sf::Image& img, int x, int y, glm::vec3 color);
void LightOnFireTanana(Sphere s, Light l, Pixel px, glm::vec3& color, glm::vec3 intersection_position, glm::vec3 lamp_direction);
bool IntersectObject(Sphere s, Light *l, Pixel px, glm::vec3& intersect, glm::vec3& color);
void IntersectObjects(Sphere *spheres, Light *l, Pixel px, sf::Image& img);
void RayCastCamera(Camera& c, Sphere *spheres, Light *l, sf::Image& img);
