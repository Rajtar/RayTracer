#include <iostream>
#include <memory>
#include "Vector3.h"
#include "Sphere.h"

int main() {
    Vector3 v = Vector3(0, 0, 0);
    Sphere s = Sphere(v, 10);
    Ray r = Ray(Vector3(0, 0, -11), Vector3(1, 1, 1));

    for (const auto &item : s.intersect(r)) {
        std::cout<<item;
    }

    return 0;
}

