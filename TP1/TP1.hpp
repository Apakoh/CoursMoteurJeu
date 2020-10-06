#include <glm/glm.hpp>
#include <sfml/graphics.hpp>
#include <sfml/graphics/image.hpp>
#include "Pixel.cpp"
#include "Scene.cpp"


void CreateWindow(Camera c);
bool ShortestIntersection(Scene* _scene, Pixel* px, glm::vec3& intersection, glm::vec3& normal, Sphere& sph);
void SetPixelCamera(sf::Image* img, int x, int y, glm::vec3 color);
void LightOnFireTanana(Sphere s, Light l, Pixel* px, glm::vec3& color, glm::vec3& intersection_position, glm::vec3& normal, glm::vec3& lamp_direction);
void IntersectObjects(Sphere& s, Scene* _scene, Pixel* px, glm::vec3& intersect, glm::vec3& normal, glm::vec3& color);
void LightsToObjects(Scene* _scene, Pixel* px);
void RayCastCamera(Scene* _scene);
