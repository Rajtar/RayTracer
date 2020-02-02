#include "Ray.h"

Ray::Ray(Vector3 origin, Vector3 target) : origin(origin), target(target) {
    direction = (target - origin).normalized();
}