#include <iostream>
#include <memory>
#include "Vector3.h"
#include "Sphere.h"
#include "Plane.h"
#include "bitmap_image.hpp"

int main() {

    const unsigned int width = 1920,
                       height = 1080;

    bitmap_image image(width,height);
    image.set_all_channels(0, 0, 0);

    for(int x=0; x < width; x++) {
        for(int y=0; y < height; y++) {
            if(x % 2 == 0 && y % 2 == 0) {
                image.set_pixel(x, y, rgb(255, 255, 255));
            }
        }
    }

    image.save_image("output.bmp");

    return 0;
}

