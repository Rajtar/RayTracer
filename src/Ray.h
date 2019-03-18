#ifndef RENDERER_RAY_H
#define RENDERER_RAY_H


#include "Vector.h"

class Ray {
public:
    Vector origin,
           direction,
           destination;

    float distance = 0.0;

    Ray(Vector origin, Vector direction);
    Ray();
};


#endif //RENDERER_RAY_H
