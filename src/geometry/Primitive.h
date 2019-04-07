#ifndef RENDERER_PRIMITIVE_H
#define RENDERER_PRIMITIVE_H

#include <vector>
#include "Vector3.h"
#include "Ray.h"
#include "../LightIntensity.h"

class Primitive {
public:
    LightIntensity color;

    Primitive(LightIntensity color) : color(color) {}

    virtual bool intersect(const Ray &ray, std::vector<Vector3> &intersections) const = 0;
};


#endif //RENDERER_PRIMITIVE_H
