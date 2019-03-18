#include <iostream>
#include "Vector.h"

int main() {
    Vector v = Vector(0, 1, 2);
    Vector a = Vector();
    std::cout << a + 2 << std::endl;
    return 0;
}

