//
// Created by jakub on 18.03.2019.
//

#include "Ray.h"

Ray::Ray(Vector origin, Vector direction) : origin(origin), direction(direction) {}

Ray::Ray() : origin(Vector()), direction(Vector()) {}
