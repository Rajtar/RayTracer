#include <cmath>
#include <memory>
#include "Sphere.h"

Sphere::Sphere(Vector3 center, float radius, const Material &material) : Primitive(material), center(center), radius(radius) {}

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

void Sphere::getTexelCoordinates(const Vector3 &intersection, const int textureWidth, const int textureHeight, int &row,
                                 int &column) const {
    Vector3 localIntersectionCoords = (this->center - intersection).normalized();

    float u = 0.5f + ((atan2f(localIntersectionCoords.z, localIntersectionCoords.x)/(2.0 * M_PI)));
    float v = 0.5f - asinf(localIntersectionCoords.y) / M_PI;

    column = (int) (textureWidth - 1) * u;
    row = (int) (textureHeight - 1) * v;
}
