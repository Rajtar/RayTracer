#ifndef RENDERER_PRIMITIVE_H
#define RENDERER_PRIMITIVE_H

#include <vector>
#include "Vector3.h"
#include "Ray.h"

class Primitive {
public:
    virtual bool intersect(const Ray &ray, std::vector<Vector3> &intersections);
};


#endif //RENDERER_PRIMITIVE_H
