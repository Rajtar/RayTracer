#ifndef RENDERER_PRIMITIVE_H
#define RENDERER_PRIMITIVE_H

#include <vector>
#include "Vector3.h"
#include "Ray.h"
#include "../light/Material.h"

class Primitive {
public:
    Primitive() = default;
    explicit Primitive(LightIntensity color);
    explicit Primitive(Material material);

    virtual bool intersect(const Ray &ray, std::vector<Vector3> &intersections) const = 0;

    LightIntensity getDiffuse() const;
    LightIntensity getAmbient() const;
    LightIntensity getSpecular() const;

private:
    Material material;
};

#endif //RENDERER_PRIMITIVE_H
