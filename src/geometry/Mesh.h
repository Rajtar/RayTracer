#ifndef RENDERER_MESH_H
#define RENDERER_MESH_H


#include "Primitive.h"
#include "Triangle.h"
#include "Intersection.h"

class Mesh : public Primitive {
public:
    std::vector<Triangle> faces;

    Mesh(Material material);

    std::vector<Intersection> intersect(const Ray &ray) const override;
};


#endif //RENDERER_MESH_H
