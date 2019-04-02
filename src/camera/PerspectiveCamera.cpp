#include <iostream>
#include "PerspectiveCamera.h"
#include "../static/Settings.hpp"

PerspectiveCamera::PerspectiveCamera(Vector3 position, Vector3 direction, float viewportDistance, Vector3 up) : Camera(
        position, direction, viewportDistance, up) {}

void PerspectiveCamera::renderScene(const Scene &scene, std::unique_ptr<Image> &image) {
    unsigned int imageWidth = image->getWidth();
    unsigned int imageHeight = image->getHeight();

    float pixelHeight = 2.0F / imageWidth;
    float pixelWidth = 2.0F / imageHeight;

    if(Settings::AntialiasingType == None) {
        for (unsigned int x = 0; x < imageWidth; x++) {
            for (unsigned int y = 0; y < imageHeight; y++) {
                float xCenter = -1.0F + (x + 0.5F) * pixelWidth;
                float yCenter = 1.0F - (y + 0.5F) * pixelHeight;

                Ray ray(this->position, Vector3(xCenter, yCenter, static_cast<int>(viewportDistance)));

                std::vector<Vector3> intersections;
                for (const auto &primitive : scene.primitives) {
                    if (primitive->intersect(ray, intersections)) {
                        image->writePixel(x, y, LightIntensity(1.0, 0.0, 0.0));
                    } else {
                        image->writePixel(x, y, LightIntensity(0.0, 0.0, 0.0));
                    }
                }
            }
        }
    }
    else if(Settings::AntialiasingType == MultiSampling) {
        for (unsigned int x = 0; x < imageWidth; x++) {
            for (unsigned int y = 0; y < imageHeight; y++) {
                float xUpperLeft = -1.0F + x * pixelWidth;
                float yUpperLeft = 1.0F - y * pixelHeight;

                float xLowerLeft = -1.0F + x * pixelWidth;
                float yLowerLeft = 1.0F - (y + 1) * pixelHeight;

                float xCenter = -1.0F + (x + 0.5F) * pixelWidth;
                float yCenter = 1.0F - (y + 0.5F) * pixelHeight;

                float xUpperRight = -1.0F + (x + 1) * pixelWidth;
                float yUpperRight = 1.0F - y * pixelHeight;

                float xLowerRight = -1.0F + (x + 1) * pixelWidth;
                float yLowerRight = 1.0F - (y + 1) * pixelHeight;

                Ray rays[] {
                    Ray(this->position, Vector3(xCenter, yCenter, viewportDistance)),
                    Ray(this->position, Vector3(xUpperLeft, yUpperLeft, viewportDistance)),
                    Ray(this->position, Vector3(xLowerLeft, yLowerLeft, viewportDistance)),
                    Ray(this->position, Vector3(xUpperRight, yUpperRight, viewportDistance)),
                    Ray(this->position, Vector3(xLowerRight, yLowerRight, viewportDistance))
                };

                Vector3 lightIntensity(0, 0, 0);

                std::vector<Vector3> intersections;
                for (const auto &primitive : scene.primitives) {
                    for (const auto &ray : rays) {
                        if (primitive->intersect(ray, intersections)) {
                            lightIntensity += Vector3(0.0, 1.0, 0.0);
                        }
                    }
                }

                lightIntensity /= 5;
                image->writePixel(x, y, LightIntensity(lightIntensity.x, lightIntensity.y, lightIntensity.z));
            }
        }
    }
}
