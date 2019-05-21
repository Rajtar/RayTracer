#ifndef RENDERER_PRIMITIVE_H
#define RENDERER_PRIMITIVE_H

#include <vector>
#include "Vector3.h"
#include "Ray.h"
#include "../light/Material.h"

class Primitive {
public:
    Material material;

    Primitive() = default;
    explicit Primitive(LightIntensity color);
    explicit Primitive(Material material);

    virtual bool intersect(const Ray &ray, std::vector<Vector3> &intersections) const = 0;
    virtual Vector3 getNormalAt(Vector3 point) = 0;

    LightIntensity getDiffuse() const;
    LightIntensity getAmbient() const;
    LightIntensity getSpecular() const;
    double getSmoothness() const ;
};

#endif //RENDERER_PRIMITIVE_H
