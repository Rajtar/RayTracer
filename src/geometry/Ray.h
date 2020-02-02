#ifndef RENDERER_RAY_H
#define RENDERER_RAY_H


#include "Vector3.h"

class Ray {
public:
    Vector3 origin = Vector3(0),
            target = Vector3(0),
            direction = Vector3(0);

    Ray(Vector3 origin, Vector3 target);

    Ray() = default;
};


#endif //RENDERER_RAY_H
