#ifndef RENDERER_RAY_H
#define RENDERER_RAY_H


#include "Vector3.h"

class Ray {
public:
    Vector3 origin,
           direction,
           destination;

    float distance = 0.0;

    Ray(Vector3 origin, Vector3 direction);
    Ray();
};


#endif //RENDERER_RAY_H
