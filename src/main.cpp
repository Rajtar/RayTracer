#include <iostream>
#include "Vector.h"
#include "Sphere.h"

int main() {
    Vector v = Vector(0, 1, 2);
    Sphere s = Sphere(v, 5);
    std::cout << s.center << " : " << s.radius << std::endl;
    return 0;
}

