#ifndef RENDERER_PRIMITIVE_H
#define RENDERER_PRIMITIVE_H

#include <vector>
#include "Vector3.h"
#include "Ray.h"
#include "../LightIntensity.h"
#include "../Material.h"

class Primitive {
public:

    Primitive(LightIntensity color) {
        material = Material(color, color, color, color);
    }
    Primitive(Material material) : material(material) {}

    virtual bool intersect(const Ray &ray, std::vector<Vector3> &intersections) const = 0;

    LightIntensity getDiffuse() const {
        return material.diffuse;
    }

    LightIntensity getAmbient() const {
        return material.ambient;
    }

    LightIntensity getSpecular() const {
        return material.specular;
    }

private:
    Material material;
};


#endif //RENDERER_PRIMITIVE_H
