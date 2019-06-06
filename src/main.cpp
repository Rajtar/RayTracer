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
#include "light/Texture.h"
#include <chrono>

const std::string currentDateTime();
void drawGrid(Image &image, int density, unsigned char color);

int main() {
    const unsigned int width = 1000,
                       height = 1000;

    OBJLoader loader;

    BitmapImage colorfulBMP("../textures/colorful.bmp");
    BitmapImage checkerBMP("../textures/checker.bmp");

    Texture colorfulTexture(colorfulBMP);
    Texture checkerTexture(checkerBMP);

    Material red(LightIntensity(1, 0, 0), LightIntensity(1, 0, 0), LightIntensity(0.8, 0.8, 0.8), 0.9);
    Material blue(LightIntensity(0, 0, 1), LightIntensity(0, 0, 0), LightIntensity(0.8, 0.8, 0.8), 0.9);
    Material yellow(LightIntensity(1, 1, 0), LightIntensity(1, 1, 0), LightIntensity(0.8, 0.8, 0.8), 0.9);
    Material white(LightIntensity(1, 1, 1), LightIntensity(1, 1, 1), LightIntensity(0.8, 0.8, 0.8), 0.9);
    Material green(LightIntensity(0, 1, 0), LightIntensity(0, 1, 0), LightIntensity(0.8, 0.8, 0.8), 0.9);
    Material colorful(colorfulTexture, LightIntensity(1, 1, 1), LightIntensity(1, 1, 1), LightIntensity(0.8, 0.8, 0.8), 0.9);
    Material checker(checkerTexture, LightIntensity(1, 1, 1), LightIntensity(1, 1, 1), LightIntensity(0.8, 0.8, 0.8), 0.9);

    std::shared_ptr<Mesh> mesh(new Mesh(red));
    std::shared_ptr<Plane> floor(new Plane(Vector3(0, -10, 0), Vector3(0, 1, 0), white));
    std::shared_ptr<Plane> roof(new Plane(Vector3(0, 15, 0), Vector3(0, -1, 0), white));
    std::shared_ptr<Plane> backWall(new Plane(Vector3(0, 0, 40), Vector3(0, 0, -1), white));
    std::shared_ptr<Plane> rightWall(new Plane(Vector3(15, 0, 0), Vector3(-1, 0, 0), green));
    std::shared_ptr<Plane> leftWall(new Plane(Vector3(-15, 0, 0), Vector3(1, 0, 0), red));
    std::shared_ptr<Sphere> sphere1(new Sphere(Vector3(0, -2, 30), 3, colorful));

//    loader.loadMesh("../models/dodecahedron.obj", mesh, true, Vector3(0, -2, 15));

    std::shared_ptr<PointLight> whiteLight(
            new PointLight(LightIntensity(0.8, 0.8, 0.4), LightIntensity(0.3, 0.3, 0.3), LightIntensity(0.5, 0.5, 0.5),
                           Vector3(0, 9, 30)));

    Scene scene;
    scene.addPrimitive(sphere1);
    scene.addPrimitive(floor);
    scene.addPrimitive(roof);
    scene.addPrimitive(rightWall);
    scene.addPrimitive(leftWall);
    scene.addPrimitive(backWall);
//    scene.addPrimitive(mesh);
    scene.addLight(whiteLight);

    PerspectiveCamera camera(Vector3(0, 0, 0), Vector3(0, 0, 0), 2);
    std::unique_ptr<Image> image(new BitmapImage(width, height));

    image.get()->writeAll(86, 151, 255);

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

