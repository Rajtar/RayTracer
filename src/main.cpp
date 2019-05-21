#include <iostream>
#include <memory>
#include "geometry/Sphere.h"
#include "Scene.h"
#include "camera/PerspectiveCamera.h"
#include "geometry/Triangle.h"
#include "io/image/BitmapImage.h"
#include "io/mesh/OBJLoader.h"
#include "static/StringUtils.h"
#include "camera/OrthographicCamera.h"
#include "geometry/Plane.h"
#include "light/PointLight.h"
#include <chrono>

const std::string currentDateTime();
void drawGrid(Image &image, int density, unsigned char color);

int main() {
    const unsigned int width = 500,
                       height = 500;

    OBJLoader loader;

    Material red(LightIntensity(1, 0, 0), LightIntensity(0, 0, 0), LightIntensity(0.8, 0.8, 0.8), 0.9);
    Material blue(LightIntensity(0, 0, 1), LightIntensity(0, 0, 0), LightIntensity(0.8, 0.8, 0.8), 0.9);

//    std::shared_ptr<Mesh> mesh(new Mesh(LightIntensity(0.33, 0.66, 0.99)));
//    std::shared_ptr<Plane> floor(new Plane(Vector3(0, -4, 6), Vector3(0, 1, 0), LightIntensity(0, 1, 0)));
    std::shared_ptr<Triangle> triangle(new Triangle(Vector3(-1, -2, 1), Vector3(1, -2, 1), Vector3(0, 2, 1), blue));
    std::shared_ptr<Sphere> sphere1(new Sphere(Vector3(0, 0, 15), 3, red));

//    loader.loadMesh("../models/teapot.obj", mesh, Vector3(0, 0, 5));

    std::shared_ptr<PointLight> pointLight(new PointLight(LightIntensity(1, 1, 1), LightIntensity(1, 1, 1), LightIntensity(0.2, 0.2, 0.2), Vector3(0, 0, -5), 1, 1, 1));

    Scene scene;
    scene.addPrimitive(sphere1);
//    scene.addPrimitive(triangle);
    scene.addLight(pointLight);

    PerspectiveCamera camera(Vector3(0, 0, 0), Vector3(0, 0, 0), 2);
    std::unique_ptr<Image> image(new BitmapImage(width, height));

    drawGrid(*image, 25, 50);

    std::cout << "Rendering scene with: " << scene.primitives.size() << (scene.primitives.size() == 1 ? " object\n" : " objects\n") ;
    auto startTime = std::chrono::system_clock::now();
    camera.renderScene(scene, image);
    auto endTime = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    std::cout<< "Rendering took: " << elapsedSeconds.count() << "s\n";

    std::string fileName = currentDateTime() + ".bmp";
    image->saveToFile(fileName);

    std::cout<< "Saved image as: " << fileName << std::endl;
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

void drawGrid(Image &image, int density, unsigned char color) {
    for (unsigned int x = 0; x < image.getWidth(); x++) {
        for (unsigned int y = 0; y < image.getHeight(); y++) {
            if(x % density == 0 || y % density == 0) {
                image.writePixel(x, y, color, color, color);
            }
        }
    }
}

