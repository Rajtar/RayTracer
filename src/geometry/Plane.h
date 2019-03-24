#ifndef RENDERER_PLANE_H
#define RENDERER_PLANE_H


#include "Vector3.h"
#include "Ray.h"
#include "Primitive.h"

class Plane : public Primitive {
public:
    /// Point that the plane contains
    Vector3 point;
    Vector3 normal;

    Plane(const Vector3& point, const Vector3& normal);

    bool intersect(const Ray &ray, std::vector<Vector3> &intersections) override;
};


#endif //RENDERER_PLANE_H
