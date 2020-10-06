#include "Sphere.cpp"
#include "Camera.cpp"
#include "Light.cpp"

class Scene
{
  public:
    Camera* camera;
    Light* lights;
    Sphere* spheres;

    Scene(Camera* _camera, Light* _lights, Sphere* _spheres)
    {
      camera = _camera;
      lights = _lights;
      spheres = _spheres;
    }
};
