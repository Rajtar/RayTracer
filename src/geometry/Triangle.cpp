//
// Created by jakub on 06.04.2019.
//

#include "Triangle.h"

Triangle::Triangle(const Vector3 &a, const Vector3 &b, const Vector3 &c, const Vector3 &normal,
                   LightIntensity color) : Primitive(color),
                                           a(a),
                                           b(b),
                                           c(c) {
    this->normal = normal.normalize();
}

bool Triangle::intersect(const Ray &ray, std::vector<Vector3> &intersections) {


    return false;
}


