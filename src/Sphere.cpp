#include <cmath>
#include <memory>
#include "Sphere.h"

Sphere::Sphere(Vector3 center, float radius) : center(center), radius(radius) {}

std::vector<Vector3> Sphere::intersect(const Ray &ray) {
    Vector3 oc = ray.origin - center;
    float a = ray.direction.dot(ray.direction);
    float b = 2 * oc.dot(ray.direction);
    float c = oc.dot(oc) - radius * radius;
    double delta = b * b - 4 * a * c;

    std::vector<Vector3> intersections;

    if (delta > 0) {
        float f0 = (-b - sqrt(delta)) / (2.0 * a);
        float f1 = (-b + sqrt(delta)) / (2.0 * a);

        if(f0 >= 0) {
            intersections.push_back(f0 * ray.direction + ray.origin);
        }
        if(f1 >= 0) {
            intersections.push_back(f1 * ray.direction + ray.origin);
        }

        return intersections;
    }
    if (delta == 0) {
        float f = (-b / (2.0 * a));

        intersections.push_back(f * ray.direction + ray.origin);

        return intersections;
    }
    if (delta < 0) {
        return intersections;
    }
}
