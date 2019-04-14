#ifndef RENDERER_TRIANGLE_H
#define RENDERER_TRIANGLE_H


#include "Primitive.h"

class Triangle : public Primitive {
public:
    Vector3 a, b, c;
    Vector3 normal;

    Triangle(const Vector3 &a, const Vector3 &b, const Vector3 &c, LightIntensity color);
    Triangle(const Vector3 &a, const Vector3 &b, const Vector3 &c, Material material);

    bool intersect(const Ray &ray, std::vector<Vector3> &intersections) const override;
};


#endif //RENDERER_TRIANGLE_H
