#include "Sphere.cpp"
#include "Camera.cpp"
#include "Light.cpp"

class Scene
{
  public:
    Camera camera;
    Light* lights;
    Sphere* spheres;
};
