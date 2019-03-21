#include "Ray.h"

Ray::Ray(Vector3 origin, Vector3 direction) : origin(origin), direction(direction) {
    direction = direction.normalize();
}

Ray::Ray() : origin(Vector3()), direction(Vector3()) {}
