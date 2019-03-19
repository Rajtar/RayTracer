#include "Ray.h"

Ray::Ray(Vector origin, Vector direction) : origin(origin), direction(direction) {}

Ray::Ray() : origin(Vector()), direction(Vector()) {}
