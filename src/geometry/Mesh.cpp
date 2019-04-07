#include "Mesh.h"

Mesh::Mesh(const LightIntensity &color) : Primitive(color) {}

bool Mesh::intersect(const Ray &ray, std::vector<Vector3> &intersections) const {
    for (const auto &face : faces) {
        std::vector<Vector3> faceIntersections;
        if(face.intersect(ray, faceIntersections)) {
            intersections.push_back(faceIntersections.front());
            return true;
        }
    }
    return false;
}
