#ifndef RENDERER_PLANE_H
#define RENDERER_PLANE_H


#include "Vector3.h"
#include "Ray.h"

class Plane {
public:
    /// Point that the plain contains
    Vector3 point;
    Vector3 normal;

    Plane(const Vector3& point, const Vector3& normal);

    bool intersect(const Ray &ray, Vector3& intersection);
};


#endif //RENDERER_PLANE_H
