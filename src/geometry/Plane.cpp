
#include "Plane.h"

Plane::Plane(const Vector3& point, const Vector3& normal) : point(point) {
    this->normal = normal.normalize();
}

bool Plane::intersect(const Ray &ray, Vector3& intersection) {
    float denominator = this->normal.dot(ray.direction);
    if(denominator > 0) {
        Vector3 distance = this->point - ray.origin;
        float t = distance.dot(this->normal) / denominator;

        if(t > 0) {
            intersection = t * ray.direction + ray.origin;
            return true;
        }
    }

    return false;
}