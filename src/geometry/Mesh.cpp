#include <algorithm>
#include "Mesh.h"

Mesh::Mesh(const Material &material) : Primitive(material) {}

std::vector<Intersection> Mesh::intersect(const Ray &ray) const {
    std::vector<Intersection> meshIntersections;
    for (const auto &face : faces) {
        std::vector<Intersection> faceIntersections = face.intersect(ray);
        if (!faceIntersections.empty()) {
            meshIntersections.push_back(faceIntersections.front());
        }
    }

    if(!meshIntersections.empty()) {
        std::sort(meshIntersections.begin(), meshIntersections.end(), [&ray] ( Intersection a, Intersection b ) {
            return (a.position - ray.origin).getMagnitude() < (b.position - ray.origin).getMagnitude();
        });
    }

    return meshIntersections;
}

void Mesh::getTexelCoordinates(const Vector3 &intersection, const int textureWidth, const int textureHeight, int &row,
                               int &column) const {
    //TODO
}
