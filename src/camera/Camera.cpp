#include <limits>
#include <cmath>
#include <iostream>
#include "Camera.h"
#include "../static/Settings.hpp"

#define PROGRESS_LOG  true

Camera::Camera(Vector3 position, Vector3 direction, double viewportDistance, Vector3 up) : position(position),
                                                                                          direction(direction),
                                                                                          viewportDistance(viewportDistance),
                                                                                          up(up) {}

void Camera::renderScene(const Scene &scene, std::unique_ptr<Image> &targetImage) {
    if(Settings::AntialiasingType == None) {
        renderSceneNoneAntialiasing(scene, targetImage);
    }
    else if(Settings::AntialiasingType == MultiSampling) {
        renderSceneMultisapmleAntialiasing(scene, targetImage);
    }
}

void Camera::renderSceneNoneAntialiasing(const Scene &scene, std::unique_ptr<Image> &targetImage) {
    unsigned int imageWidth = targetImage->getWidth();
    unsigned int imageHeight = targetImage->getHeight();

    double pixelHeight = 2.0F / imageWidth;
    double pixelWidth = 2.0F / imageHeight;

    for (unsigned int x = 0; x < imageWidth; x++) {

        #if PROGRESS_LOG
            float progress = ((float) x / (float) imageWidth) * 100;
            if(fmodf(progress, 10) == 0) {
                std::cout<< " - " << progress << "%" << std::endl;
            }
        #endif

        for (unsigned int y = 0; y < imageHeight; y++) {
            double xCenter = -1.0F + (x + 0.5F) * pixelWidth;
            double yCenter = 1.0F - (y + 0.5F) * pixelHeight;
            double lowestPixelDepth = std::numeric_limits<double>::max();

            LightIntensity pixelColor(0, 0, 0);
            Ray ray = getRay(xCenter, yCenter);
            std::vector<Vector3> intersections;

            bool intersected = false;
            for (const auto &primitive : scene.primitives) {
                if (primitive->intersect(ray, intersections)) {
                    intersected = true;
                    double intersectionDepth = (position - intersections.front()).getMagnitude();
                    if(intersectionDepth < lowestPixelDepth) {
                        lowestPixelDepth = intersectionDepth;
                        pixelColor = primitive->color;
                    }
                }
                intersections.clear();
            }
            if (intersected) {
                targetImage->writePixel(x, y, pixelColor);
            }
        }
    }
    #if PROGRESS_LOG
        std::cout<< " - " << 100 << "%" << std::endl;
    #endif
}

void Camera::renderSceneMultisapmleAntialiasing(const Scene &scene, std::unique_ptr<Image> &targetImage) {
    unsigned int imageWidth = targetImage->getWidth();
    unsigned int imageHeight = targetImage->getHeight();

    double pixelHeight = 2.0F / imageWidth;
    double pixelWidth = 2.0F / imageHeight;

    for (unsigned int x = 0; x < imageWidth; x++) {
        for (unsigned int y = 0; y < imageHeight; y++) {
            double xUpperLeft = -1.0F + x * pixelWidth;
            double yUpperLeft = 1.0F - y * pixelHeight;

            double xLowerLeft = -1.0F + x * pixelWidth;
            double yLowerLeft = 1.0F - (y + 1) * pixelHeight;

            double xCenter = -1.0F + (x + 0.5F) * pixelWidth;
            double yCenter = 1.0F - (y + 0.5F) * pixelHeight;

            double xUpperRight = -1.0F + (x + 1) * pixelWidth;
            double yUpperRight = 1.0F - y * pixelHeight;

            double xLowerRight = -1.0F + (x + 1) * pixelWidth;
            double yLowerRight = 1.0F - (y + 1) * pixelHeight;


            Ray rays[] {
                    getRay(xCenter, yCenter),
                    getRay(xUpperLeft, yUpperLeft),
                    getRay(xLowerLeft, yLowerLeft),
                    getRay(xUpperRight, yUpperRight),
                    getRay(xLowerRight, yLowerRight),
            };

            bool intersected = false;
            std::vector<Vector3> intersections;
            Vector3 pixelColor;
            for (const auto &ray : rays) {
                double lowestPixelDepth = std::numeric_limits<double>::max();
                Vector3 colorToAdd;
                for (const auto &primitive : scene.primitives) {
                    if (primitive->intersect(ray, intersections)) {
                        intersected = true;
                        double intersectionDepth = (position - intersections.front()).getMagnitude();
                        if (intersectionDepth < lowestPixelDepth) {
                            lowestPixelDepth = intersectionDepth;
                            colorToAdd = Vector3(primitive->color.r, primitive->color.g, primitive->color.b);
                        }
                    }
                    intersections.clear();
                }

                pixelColor += colorToAdd;
            }
            if(intersected) {
                pixelColor /= 5;
                targetImage->writePixel(x, y, LightIntensity(pixelColor.x, pixelColor.y, pixelColor.z));
            }
        }
    }
}
