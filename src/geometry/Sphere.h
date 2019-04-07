#ifndef RENDERER_SPHERE_H
#define RENDERER_SPHERE_H

#include <vector>
#include "Vector3.h"
#include "Ray.h"
#include "Primitive.h"

class Sphere : public Primitive {
public:
    Vector3 center;
    float radius;

    Sphere(Vector3 center, float radius, LightIntensity color);

    bool intersect(const Ray &ray, std::vector<Vector3> &intersections) const override;
};


#endif //RENDERER_SPHERE_H
