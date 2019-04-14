#ifndef RENDERER_MESH_H
#define RENDERER_MESH_H


#include "Primitive.h"
#include "Triangle.h"

class Mesh : public Primitive {
public:
    std::vector<Triangle> faces;

    explicit Mesh(const LightIntensity &color);

    bool intersect(const Ray &ray, std::vector<Vector3> &intersections) const override;
};


#endif //RENDERER_MESH_H
