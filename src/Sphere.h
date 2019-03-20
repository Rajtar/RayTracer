#ifndef RENDERER_SPHERE_H
#define RENDERER_SPHERE_H

#include <vector>
#include "Vector3.h"
#include "Ray.h"

class Sphere {
public:
    Vector3 center;
    float radius;

    Sphere() = default;
    Sphere(Vector3 center, float radius);

    std::vector<Vector3> intersect(const Ray &ray);
};


#endif //RENDERER_SPHERE_H
