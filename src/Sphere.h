#ifndef RENDERER_SPHERE_H
#define RENDERER_SPHERE_H


#include "Vector.h"

class Sphere {
public:
    Vector center;
    float radius;

    Sphere() = default;
    Sphere(Vector center, float radius);
};


#endif //RENDERER_SPHERE_H
