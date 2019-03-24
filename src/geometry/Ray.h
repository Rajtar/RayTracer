#ifndef RENDERER_RAY_H
#define RENDERER_RAY_H


#include "Vector3.h"

class Ray {
public:
    Vector3 origin,
            target,
           direction;

    Ray(Vector3 origin, Vector3 target);
    Ray();
};


#endif //RENDERER_RAY_H
