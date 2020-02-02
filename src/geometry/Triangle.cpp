#include "Triangle.h"
#include "Plane.h"
#include "Intersection.h"

#define MINUS_ZERO -0.0001

Triangle::Triangle(const Vector3 &a, const Vector3 &b, const Vector3 &c, const Vector3 &normal, const Material &material) : Primitive(material),
                                                                                                                            a(a),
                                                                                                                            b(b),
                                                                                                                            c(c),
                                                                                                                            normal(normal) {}

Triangle::Triangle(const Vector3 &a, const Vector3 &b, const Vector3 &c, const Material &material) : Primitive(material),
                                                                                                     a(a),
                                                                                                     b(b),
                                                                                                     c(c),
                                                                                                     normal((b - a).cross(c - a).normalized()){
}

std::vector<Intersection> Triangle::intersect(const Ray &ray) const {
    Plane plane(a, normal, this->material);
    std::vector<Intersection> planeIntersections = plane.intersect(ray);
    if(planeIntersections.empty()) {
        return std::vector<Intersection>();
    }

    Vector3 intersectionPosition = planeIntersections.front().position;
    Vector3 aToIntersection = this->a - intersectionPosition;
    Vector3 bToIntersection = this->b - intersectionPosition;
    Vector3 cToIntersection = this->c - intersectionPosition;
    Vector3 pairs[3] = {
            aToIntersection.cross(bToIntersection),
            bToIntersection.cross(cToIntersection),
            cToIntersection.cross(aToIntersection)
    };

    for(const auto &pair : pairs) {
        if(pair.dot(this->normal) < MINUS_ZERO) {
            return std::vector<Intersection>();
        }
    }

    std::vector<Intersection> intersections;
    Intersection intersection(intersectionPosition, this->normal);
    intersections.push_back(intersection);
    return intersections;
}

void
Triangle::getTexelCoordinates(const Vector3 &intersection, const int textureWidth, const int textureHeight, int &row,
                              int &column) const {
    //TODO
}


