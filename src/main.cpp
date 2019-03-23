#include <iostream>
#include <memory>
#include "geometry/Vector3.h"
#include "geometry/Sphere.h"
#include "geometry/Plane.h"
#include "image/bitmap_image.hpp"
#include "image/BitmapImage.h"

int main() {

    const unsigned int width = 1920,
                       height = 1080;

    std::unique_ptr<Image> image(new BitmapImage(1920, 1080));
    image->writeAll(LightIntensity(0.0, 0.0, 0.0));

    for(unsigned int x=0; x < width; x++) {
        for(unsigned int y=0; y < height; y++) {
            if(x % 2 == 0 && y % 2 == 0) {
                image->writePixel(x, y, LightIntensity(1.0, 0.0, 0.0));
            }
        }
    }

    image->saveToFile("output.bmp");
    return 0;
}

