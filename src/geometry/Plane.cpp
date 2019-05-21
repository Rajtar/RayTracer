
#include "Plane.h"

Plane::Plane(const Vector3 &point, const Vector3 &normal, Material material) : Primitive(material), point(point) {
    this->normal = normal.normalized();
}

bool Plane::intersect(const Ray &ray, std::vector<Vector3> &intersections) const {
    double denominator = this->normal.dot(ray.direction);
    if(denominator > 0) {
        Vector3 distance = this->point - ray.origin;
        double t = distance.dot(this->normal) / denominator;

        if(t > 0) {
            intersections.push_back(t * ray.direction + ray.origin);
            return true;
        }
    }

    return false;
}

Vector3 Plane::getNormalAt(Vector3 point) {
    return this->normal;
}
