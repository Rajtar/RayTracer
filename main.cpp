#include <iostream>
#include "Vector.h"

int main() {

    Vector v = Vector(0, 1, 2);
    v.normalize();
    std::cout << v << std::endl;
    std::cout << v + v << std::endl;
    return 0;
}

