#include <glm/glm.hpp>
#include <sfml/graphics.hpp>
#include <sfml/graphics/image.hpp>
#include "Pixel.cpp"
#include "Scene.cpp"


void CreateWindow(Camera c);
bool RaySphereIntersect(glm::vec3 &r_origin, glm::vec3 &r_direction, glm::vec3 &sphere_center, float sphere_radius, glm::vec3 &position, glm::vec3 &normal);
bool ShortestIntersection(Sphere *spheres, Pixel* px, glm::vec3& intersection, glm::vec3& normal, Sphere& sph);
void SetPixelCamera(sf::Image* img, int x, int y, glm::vec3 color);
void LightOnFireTanana(Sphere s, Light l, Pixel* px, glm::vec3& color, glm::vec3& intersection_position, glm::vec3& normal, glm::vec3& lamp_direction);
void IntersectObjects(Sphere s, Light *l, Pixel* px, glm::vec3& intersect, glm::vec3& normal, glm::vec3& color, Sphere *spheres);
void LightsToObjects(Scene* _scene, Pixel* px);
void RayCastCamera(Scene* _scene);
