
#include <cmath>
#include "Plane.h"
#include "Intersection.h"

Plane::Plane(const Vector3 &point, const Vector3 &normal, Material material) : Primitive(material), point(point) {
    this->normal = normal.normalized();
}

std::vector<Intersection> Plane::intersect(const Ray &ray) const {
    double denominator = this->normal.dot(ray.direction);
    std::vector<Intersection> intersections;
    if(fabs(denominator) > 0.0001f) {
        Vector3 distance = this->point - ray.origin;
        double t = distance.dot(this->normal) / denominator;
        if(t > 0) {
            Intersection intersection(t * ray.direction + ray.origin, this->normal);
            intersections.push_back(intersection);
        }
    }
    return intersections;
}

void Plane::getTexelCoordinates(const Vector3 &intersection, const int textureWidth, const int textureHeight, int &row,
                                int &column) const {
    Vector3 localIntersectionCoords = (this->point - intersection).normalized();

    float u = (localIntersectionCoords.z + 1) / 2.0f;
    float v = (localIntersectionCoords.x + 1) / 2.0f;

    column = (int) (textureWidth - 1) * u;
    row = (int) (textureHeight - 1) * v;
}

