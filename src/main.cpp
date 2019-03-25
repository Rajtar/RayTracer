#include <iostream>
#include <memory>
#include "geometry/Sphere.h"
#include "image/bitmap_image.hpp"
#include "image/BitmapImage.h"
#include "Scene.h"
#include "PerspectiveCamera.h"

int main() {
    const unsigned int width = 1920,
                       height = 1080;
    //image->writeAll(LightIntensity(0.0, 0.0, 0.0));

//    for(unsigned int x=0; x < width; x++) {
//        for(unsigned int y=0; y < height; y++) {
//            if(x % 10 == 0 && y % 10 == 0) {
//                image->writePixel(x, y, LightIntensity(1.0, 0.0, 0.0));
//            }
//        }
//    }

    Sphere sphere(Vector3(0, 0, 2), 10);
    Scene scene;
    scene.AddPrimitive(sphere);

    PerspectiveCamera camera(Vector3(0, 0, -2), Vector3(0, 0, -2), Vector3(0, 0, -2), 1, 1, 1);
    std::unique_ptr<Image> image(new BitmapImage(width, height));
    camera.renderScene(scene, image);

    image->saveToFile("output.bmp");
    return 0;
}

