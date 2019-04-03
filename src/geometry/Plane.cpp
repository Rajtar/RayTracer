
#include "Plane.h"

Plane::Plane(const Vector3 &point, const Vector3 &normal, LightIntensity color) : Primitive(color), point(point) {
    this->normal = normal.normalize();
}

bool Plane::intersect(const Ray &ray, std::vector<Vector3> &intersections) {
    float denominator = this->normal.dot(ray.direction);
    if(denominator > 0) {
        Vector3 distance = this->point - ray.origin;
        float t = distance.dot(this->normal) / denominator;

        if(t > 0) {
            intersections.push_back(t * ray.direction + ray.origin);

            return true;
        }
    }

    return false;
}
