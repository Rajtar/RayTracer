#ifndef RENDERER_PLANE_H
#define RENDERER_PLANE_H


#include "Vector3.h"
#include "Ray.h"
#include "Primitive.h"
#include "Intersection.h"

class Plane : public Primitive {
public:
    /// Point that the plane contains
    Vector3 point;
    Vector3 normal;

    Plane(const Vector3 &point, const Vector3 &normal, Material material);

    std::vector<Intersection> intersect(const Ray &ray) const override;
};


#endif //RENDERER_PLANE_H
