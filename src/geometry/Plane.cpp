
#include "Plane.h"
#include "Intersection.h"

Plane::Plane(const Vector3 &point, const Vector3 &normal, Material material) : Primitive(material), point(point) {
    this->normal = normal.normalized();
}

std::vector<Intersection> Plane::intersect(const Ray &ray) const {
    double denominator = this->normal.dot(ray.direction);
    std::vector<Intersection> intersections;
    if(denominator > 0) {
        Vector3 distance = this->point - ray.origin;
        double t = distance.dot(this->normal) / denominator;
        if(t > 0) {
            Intersection intersection(t * ray.direction + ray.origin, this->normal);
            intersections.push_back(intersection);
        }
    }
    return intersections;
}

