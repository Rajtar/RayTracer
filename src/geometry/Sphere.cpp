#include <cmath>
#include <memory>
#include "Sphere.h"

Sphere::Sphere(Vector3 center, float radius) : center(center), radius(radius) {}

bool Sphere::intersect(const Ray &ray, std::vector<Vector3> &intersections) {
    Vector3 rayDirection(ray.direction.normalize());

    Vector3 oc = ray.origin - center;
    float a = rayDirection.dot(rayDirection);
    float b = 2 * oc.dot(rayDirection);
    float c = oc.dot(oc) - radius * radius;
    double delta = b * b - 4 * a * c;

    if (delta > 0) {
        float f0 = (-b - sqrt(delta)) / (2.0 * a);
        float f1 = (-b + sqrt(delta)) / (2.0 * a);

        if(f0 >= 0) {
            intersections.push_back(f0 * rayDirection + ray.origin);
        }
        if(f1 >= 0) {
            intersections.push_back(f1 * rayDirection + ray.origin);
        }

        return !intersections.empty();
    }
    if (delta == 0) {
        float f = (-b / (2.0 * a));

        intersections.push_back(f * rayDirection + ray.origin);

        return true;
    }
    if (delta < 0) {
        return false;
    }
    return false;
}
