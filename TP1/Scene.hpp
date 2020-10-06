#include "Sphere.cpp"
#include "Camera.cpp"
#include "Light.cpp"

class Scene
{
  public:
    Camera* camera;
    std::vector<Light> lights;
    std::vector<Sphere> spheres;

    int nb_sphere = 0;
    int nb_light = 0;

    Scene(Camera* _camera)
    {
      camera = _camera;
    }

    void AddSphere(Sphere& _sphere)
    {
      spheres.push_back(_sphere);
      nb_sphere++;
    }

    void AddLight(Light& _light)
    {
      lights.push_back(_light);
      nb_light++;
    }
};
