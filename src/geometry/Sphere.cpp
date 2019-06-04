#include <cmath>
#include <memory>
#include "Sphere.h"

Sphere::Sphere(Vector3 center, float radius, Material material) : Primitive(material), center(center), radius(radius) {}

std::vector<Intersection> Sphere::intersect(const Ray &ray) const {
    std::vector<Intersection> intersections;

    Vector3 rayDirection(ray.direction.normalized());
    Vector3 oc = ray.origin - center;
    double a = rayDirection.dot(rayDirection);
    double b = 2 * oc.dot(rayDirection);
    double c = oc.dot(oc) - radius * radius;
    double delta = b * b - 4 * a * c;

    if (delta > 0) {
        double f0 = (-b - sqrt(delta)) / (2.0 * a);
        double f1 = (-b + sqrt(delta)) / (2.0 * a);

        if (f0 >= 0) {
            Vector3 intersectionPosition = f0 * rayDirection + ray.origin;
            Intersection intersection(intersectionPosition, getNormalAt(intersectionPosition));
            intersections.push_back(intersection);
        }
        if (f1 >= 0) {
            Vector3 intersectionPosition = f1 * rayDirection + ray.origin;
            Intersection intersection(intersectionPosition, getNormalAt(intersectionPosition));
            intersections.push_back(intersection);
        }

    } else if (delta == 0) {
        double f = (-b / (2.0 * a));
        if (f > 0) {
            Vector3 intersectionPosition = f * rayDirection + ray.origin;
            Intersection intersection(intersectionPosition, getNormalAt(intersectionPosition));
            intersections.push_back(intersection);
        }
    }

    return intersections;
}

Vector3 Sphere::getNormalAt(Vector3 point) const {
    return (point - this->center).normalized();
}