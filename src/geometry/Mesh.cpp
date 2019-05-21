#include <algorithm>
#include "Mesh.h"

Mesh::Mesh(const LightIntensity &color) : Primitive(color) {}

bool Mesh::intersect(const Ray &ray, std::vector<Vector3> &intersections) const {
    for (const auto &face : faces) {
        std::vector<Vector3> faceIntersections;
        if(face.intersect(ray, faceIntersections)) {
            intersections.push_back(faceIntersections.front());
        }
    }

    if(!intersections.empty()) {
        std::sort(intersections.begin(), intersections.end(), [&ray] ( Vector3 a, Vector3 b ) {
            return (a - ray.origin).getMagnitude() < (b - ray.origin).getMagnitude();
        });
        return true;
    }

    return false;
}

Vector3 Mesh::getNormalAt(Vector3 point) {
    return Vector3(); // TODO
}
