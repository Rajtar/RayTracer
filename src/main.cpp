#include <iostream>
#include <memory>
#include "geometry/Sphere.h"
#include "image/bitmap_image.hpp"
#include "image/BitmapImage.h"
#include "Scene.h"
#include "camera/PerspectiveCamera.h"
#include "camera/OrthographicCamera.h"
#include <chrono>

const std::string currentDateTime();
void drawGrid(Image &image, int density, char color);

int main() {
    const unsigned int width = 1000,
                       height = 1000;

    Sphere s1(Vector3(0, 0, 5), 0.5);
    Sphere s2(Vector3(0.75, 0.5, 5), 0.75);
    Sphere s3(Vector3(-1, -1, 5), 3);
    Scene scene;
    scene.AddPrimitive(std::unique_ptr<Primitive>(&s3));
    scene.AddPrimitive(std::unique_ptr<Primitive>(&s1));
    scene.AddPrimitive(std::unique_ptr<Primitive>(&s2));


    PerspectiveCamera camera(Vector3(0, 0, 0), Vector3(0, 0, 0), 2);
    std::unique_ptr<Image> image(new BitmapImage(width, height));

    drawGrid(*image, 25, 50);

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
    struct tm  timeStruct{};
    char       buf[80];
    timeStruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d--%H-%M-%S", &timeStruct);
    return buf;
}

void drawGrid(Image &image, int density, char color) {
    for (unsigned int x = 0; x < image.getWidth(); x++) {
        for (unsigned int y = 0; y < image.getHeight(); y++) {
            if(x % density == 0 || y % density == 0) {
                image.writePixel(x, y, color, color, color);
            }
        }
    }
}

