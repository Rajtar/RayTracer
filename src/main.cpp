#include <iostream>
#include <memory>
#include "geometry/Sphere.h"
#include "image/bitmap_image.hpp"
#include "image/BitmapImage.h"
#include "Scene.h"
#include "camera/PerspectiveCamera.h"

int main() {
    const unsigned int width = 500,
                       height = 500;

    Sphere sphere(Vector3(0, 0, 10), 2);
    Scene scene;
    scene.AddPrimitive(std::unique_ptr<Primitive>(&sphere));

    PerspectiveCamera camera(Vector3(0, 0, 0), Vector3(0, 0, 0), 2);
    std::unique_ptr<Image> image(new BitmapImage(width, height));
    camera.renderScene(scene, image);

    image->saveToFile("output.bmp");
    return 0;
}

