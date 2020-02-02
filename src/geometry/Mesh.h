#ifndef RENDERER_MESH_H
#define RENDERER_MESH_H


#include "Primitive.h"
#include "Triangle.h"
#include "Intersection.h"

class Mesh : public Primitive {
public:
    std::vector<Triangle> faces;

    Mesh(const Material &material);

    std::vector<Intersection> intersect(const Ray &ray) const override;

    void getTexelCoordinates(const Vector3 &intersection, const int textureWidth, const int textureHeight, int &row,
                             int &column) const override;
};


#endif //RENDERER_MESH_H
