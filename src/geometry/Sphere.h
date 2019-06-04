#ifndef RENDERER_SPHERE_H
#define RENDERER_SPHERE_H

#include <vector>
#include "Vector3.h"
#include "Ray.h"
#include "Primitive.h"
#include "Intersection.h"

class Sphere : public Primitive {
public:
    Vector3 center;
    float radius;

    Sphere(Vector3 center, float radius, Material material);

    std::vector<Intersection> intersect(const Ray &ray) const override;

    void getTexelCoordinates(const Vector3 &intersection, const int textureWidth, const int textureHeight, int &row,
                             int &column) const override;

    Vector3 getNormalAt(Vector3 point) const;
};


#endif //RENDERER_SPHERE_H
