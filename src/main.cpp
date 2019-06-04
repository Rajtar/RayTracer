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
    const unsigned int width = 150,
                       height = 150;

    OBJLoader loader;

    BitmapImage brickBMP("../textures/brick.bmp");
    BitmapImage dogeBMP("../textures/doge.bmp");

    Texture brickTexture(brickBMP);
    Texture dogeTexture(dogeBMP);

    Material red(LightIntensity(1, 0, 0), LightIntensity(1, 0, 0), LightIntensity(0.8, 0.8, 0.8), 0.9);
    Material blue(LightIntensity(0, 0, 1), LightIntensity(0, 0, 0), LightIntensity(0.8, 0.8, 0.8), 0.9);
    Material yellow(LightIntensity(1, 1, 0), LightIntensity(1, 1, 0), LightIntensity(0.8, 0.8, 0.8), 0.9);
    Material brick(brickTexture, LightIntensity(1, 1, 1), LightIntensity(1, 1, 1), LightIntensity(0.8, 0.8, 0.8), 0.9);
    Material doge(dogeTexture, LightIntensity(1, 1, 1), LightIntensity(1, 1, 1), LightIntensity(0.8, 0.8, 0.8), 0.9);

    std::shared_ptr<Mesh> mesh(new Mesh(red));
    std::shared_ptr<Plane> floor(new Plane(Vector3(0, -10, 6), Vector3(0, 1, 0), doge));
//    std::shared_ptr<Triangle> triangle(new Triangle(Vector3(-1, -2, 1), Vector3(1, -2, 1), Vector3(0, 2, 1), blue));
    std::shared_ptr<Sphere> sphere1(new Sphere(Vector3(0, 2, 15), 3, brick));

    loader.loadMesh("../models/dodecahedron.obj", mesh, true, Vector3(0, -2, 15));



    std::shared_ptr<PointLight> whiteLight(
            new PointLight(LightIntensity(1, 1, 1), LightIntensity(0.2, 0.2, 0.2), LightIntensity(0.2, 0.2, 0.2),
                           Vector3(0, 5, 5)));

    Scene scene;
    scene.addPrimitive(sphere1);
    scene.addPrimitive(floor);
//    scene.addPrimitive(triangle);
//    scene.addPrimitive(mesh);
    scene.addLight(whiteLight);

    PerspectiveCamera camera(Vector3(0, 0, 0), Vector3(0, 0, 0), 2);
    std::unique_ptr<Image> image(new BitmapImage(width, height));

    image.get()->writeAll(86, 151, 255);
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

