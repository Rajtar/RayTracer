#ifndef RENDERER_INTERSECTION_H
#define RENDERER_INTERSECTION_H


#include "Vector3.h"

class Intersection {
public:
    Vector3 position = Vector3(0);
    Vector3 normal = Vector3(0);

    Intersection() = default;
    Intersection(const Vector3 &position, const Vector3 &normal);
};


#endif //RENDERER_INTERSECTION_H
