#include "Ray.h"

Ray::Ray(Vector3 origin, Vector3 direction) : origin(origin), direction(direction) {
    destination = origin + direction;
    distance = direction.getMagnitude();
}

Ray::Ray() : origin(Vector3()), direction(Vector3()) {}
