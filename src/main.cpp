#include <iostream>
#include <memory>
#include "geometry/Sphere.h"
#include "image/bitmap_image.hpp"
#include "image/BitmapImage.h"
#include "Scene.h"
#include "camera/PerspectiveCamera.h"
#include <chrono>
#include <ctime>

const std::string currentDateTime();

int main() {
    const unsigned int width = 300,
                       height = 300;

    Sphere sphere(Vector3(0, 0, -2), 0.2);
    Scene scene;
    scene.AddPrimitive(std::unique_ptr<Primitive>(&sphere));

    PerspectiveCamera camera(Vector3(0, 0, 0), Vector3(0, 0, 0), 2);
    std::unique_ptr<Image> image(new BitmapImage(width, height));

    auto startTime = std::chrono::system_clock::now();
    camera.renderScene(scene, image);
    auto endTime = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    std::cout<< "Rendering took: " << elapsedSeconds.count() << "s\n";

    std::string fileName = currentDateTime() + ".bmp";
    image->saveToFile(fileName);
    return 0;
}

const std::string currentDateTime() {
    time_t     now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d--%H-%M-%S", &tstruct);
    return buf;
}

