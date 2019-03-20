#include <iostream>
#include <memory>
#include "Vector3.h"
#include "Sphere.h"

int main() {
    Vector3 v = Vector3(0, 0, 0);
    Sphere s = Sphere(v, 5);
    Ray r = Ray(Vector3(0, 0, -20), Vector3(0, 0, 1));
    
    for (const auto &item : s.intersect(r)) {
        std::cout<<item;
    }

    return 0;
}

