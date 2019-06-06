#ifndef RENDERER_TRIANGLE_H
#define RENDERER_TRIANGLE_H


#include "Primitive.h"
#include "Intersection.h"

class Triangle : public Primitive {
public:
    Vector3 a, b, c;
    Vector3 normal;

    Triangle() = default;
    Triangle(const Vector3 &a, const Vector3 &b, const Vector3 &c, const Vector3 &normal, Material material);
    Triangle(const Vector3 &a, const Vector3 &b, const Vector3 &c, Material material);

    std::vector<Intersection> intersect(const Ray &ray) const override;

    void getTexelCoordinates(const Vector3 &intersection, const int textureWidth, const int textureHeight, int &row,
                             int &column) const override;
};


#endif //RENDERER_TRIANGLE_H
