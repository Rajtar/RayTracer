#include <cmath>
#include <memory>
#include "Sphere.h"

Sphere::Sphere(Vector3 center, float radius, LightIntensity color) : Primitive(color), center(center), radius(radius) {}

Sphere::Sphere(Vector3 center, float radius, Material material) : Primitive(material), center(center), radius(radius) {}

bool Sphere::intersect(const Ray &ray, std::vector<Vector3> &intersections) const {
    Vector3 rayDirection(ray.direction.normalized());

    Vector3 oc = ray.origin - center;
    double a = rayDirection.dot(rayDirection);
    double b = 2 * oc.dot(rayDirection);
    double c = oc.dot(oc) - radius * radius;
    double delta = b * b - 4 * a * c;

    if (delta > 0) {
        double f0 = (-b - sqrt(delta)) / (2.0 * a);
        double f1 = (-b + sqrt(delta)) / (2.0 * a);

        if(f0 >= 0) {
            intersections.push_back(f0 * rayDirection + ray.origin);
        }
        if(f1 >= 0) {
            intersections.push_back(f1 * rayDirection + ray.origin);
        }

        return !intersections.empty();
    }
    if (delta == 0) {
        double f = (-b / (2.0 * a));

        if(f > 0) {
            intersections.push_back(f * rayDirection + ray.origin);
        }

        return !intersections.empty();
    }
    if (delta < 0) {
        return false;
    }
    return false;
}

Vector3 Sphere::getNormalAt(Vector3 point) {
    return (point - this->center).normalized();
}


