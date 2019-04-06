#include "Triangle.h"
#include "Plane.h"

#define MINUS_ZERO -0.0001

Triangle::Triangle(const Vector3 &a, const Vector3 &b, const Vector3 &c, LightIntensity color) : Primitive(color),
                                                                                                 a(a),
                                                                                                 b(b),
                                                                                                 c(c) {
    this->normal = (b - a).cross(c - a).normalize();
}

bool Triangle::intersect(const Ray &ray, std::vector<Vector3> &intersections) {
    Plane plane(a, normal, color);
    std::vector<Vector3> planeIntersections;
    if(!plane.intersect(ray, planeIntersections)) {
        return false;
    }

    Vector3 intersection = planeIntersections.front();
    Vector3 aToIntersection = this->a - intersection;
    Vector3 bToIntersection = this->b - intersection;
    Vector3 cToIntersection = this->c - intersection;
    Vector3 pairs[3] = {
            aToIntersection.cross(bToIntersection),
            bToIntersection.cross(cToIntersection),
            cToIntersection.cross(aToIntersection)
    };

    for(const auto &pair : pairs) {
        if(pair.dot(this->normal) < MINUS_ZERO) {
            return false;
        }
    }

    intersections.push_back(intersection);
    return true;
}


