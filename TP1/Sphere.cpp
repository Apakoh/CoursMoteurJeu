#include "Sphere.hpp"


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
