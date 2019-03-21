#include <iostream>
#include <memory>
#include "Vector3.h"
#include "Sphere.h"
#include "Plane.h"

int main() {
    Sphere s = Sphere(Vector3(0, 0, 0), 10);
    Plane p = Plane(Vector3(0, 0, 0), Vector3(0, 1, 1));
    Ray r = Ray(Vector3(0, 0, -20), Vector3(0, 0, 20));
    Ray r1 = Ray(Vector3(0, 0, -20), Vector3(0, 1, 0));
    Ray r2 = Ray(Vector3(0, 0, 0), Vector3(0, 1, 1));

    std::cout<<"r-sphere: ";
    for (const auto &item : s.intersect(r)) {
        std::cout<<item;
    }
    std::cout<<std::endl<<"r1-sphere: ";
    for (const auto &item : s.intersect(r1)) {
        std::cout<<item;
    }
    std::cout<<std::endl<<"r2-sphere: ";
    for (const auto &item : s.intersect(r2)) {
        std::cout<<item;
    }

    std::cout<<std::endl;

    Vector3 intersection;
    std::cout<<"r1-plane: "<<p.intersect(r1, intersection)<<" ";
    std::cout<<intersection<<std::endl;

    return 0;
}

