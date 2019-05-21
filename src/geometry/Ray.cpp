#include "Ray.h"

Ray::Ray(Vector3 origin, Vector3 target) : origin(origin), target(target) {
    direction = (target - origin).normalized();
}

Ray::Ray() : origin(Vector3()), target(Vector3()), direction(Vector3()) {}
