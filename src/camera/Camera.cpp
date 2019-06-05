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
    if(Settings::AntiAliasingType == None) {
        renderSceneNoneAntiAliasing(scene, targetImage);
    }
    else if(Settings::AntiAliasingType == MultiSampling) {
        renderSceneMultisapmleAntiAliasing(scene, targetImage);
    }
}

void Camera::renderSceneNoneAntiAliasing(const Scene &scene, std::unique_ptr<Image> &targetImage) {
    unsigned int imageWidth = targetImage->getWidth();
    unsigned int imageHeight = targetImage->getHeight();

    double pixelHeight = 2.0F / imageWidth;
    double pixelWidth = 2.0F / imageHeight;

    for (unsigned int x = 0; x < imageWidth; x++) {
        #if PROGRESS_LOG
            printProgress((float) x, (float) imageWidth);
        #endif
        for (unsigned int y = 0; y < imageHeight; y++) {
            double xCenter = -1.0F + (x + 0.5F) * pixelWidth;
            double yCenter = 1.0F - (y + 0.5F) * pixelHeight;
            double lowestPixelDepth = std::numeric_limits<double>::max();

            LightIntensity pixelColor(0, 0, 0);
            Ray ray = getRay(xCenter, yCenter);

            bool intersected = false;
            for (const auto &primitive : scene.primitives) {
                std::vector<Intersection> intersections = primitive->intersect(ray);
                if (!intersections.empty()) {
                    intersected = true;
                    double intersectionDepth = (position - intersections.front().position).getMagnitude();
                    if(intersectionDepth < lowestPixelDepth) {
                        lowestPixelDepth = intersectionDepth;
                        pixelColor = calculatePixelColor(scene, primitive, intersections.front());
                    }
                }
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

void Camera::renderSceneMultisapmleAntiAliasing(const Scene &scene, std::unique_ptr<Image> &targetImage) {
    unsigned int imageWidth = targetImage->getWidth();
    unsigned int imageHeight = targetImage->getHeight();

    double pixelHeight = 2.0F / imageWidth;
    double pixelWidth = 2.0F / imageHeight;

    for (unsigned int x = 0; x < imageWidth; x++) {
        #if PROGRESS_LOG
            printProgress((float) x, (float) imageWidth);
        #endif
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
            Vector3 pixelColor;
            for (const auto &ray : rays) {
                double lowestPixelDepth = std::numeric_limits<double>::max();
                Vector3 colorToAdd;
                for (const auto &primitive : scene.primitives) {
                    std::vector<Intersection> intersections = primitive->intersect(ray);
                    if (!intersections.empty()) {
                        intersected = true;
                        double intersectionDepth = (position - intersections.front().position).getMagnitude();
                        if (intersectionDepth < lowestPixelDepth) {
                            lowestPixelDepth = intersectionDepth;
                            LightIntensity calculatedColor = calculatePixelColor(scene, primitive, intersections.front());
                            colorToAdd = Vector3(calculatedColor.r, calculatedColor.g, calculatedColor.b);
                        }
                    }
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

LightIntensity Camera::calculatePixelColor(Scene scene,
                                           std::shared_ptr<Primitive> intersectedPrimitive,
                                           Intersection intersection) {
    //TODO: check if primitive contains texture
    int textureX, textureY;
    Texture& objectTexture = intersectedPrimitive->material.texture;
    LightIntensity textureColor(1, 1, 1);

    if (!objectTexture.isEmpty()) {
        intersectedPrimitive->getTexelCoordinates(intersection.position, objectTexture.getWidth(), objectTexture.getHeight(), textureX, textureY);
        textureColor = objectTexture.getColorAt(textureX, textureY);
    }

    scene.primitives.remove(intersectedPrimitive);
    LightIntensity cumulativeIntensity;
    for (const auto &light : scene.lights) {
        cumulativeIntensity += light.get()->calculateLightIntensity(scene.primitives, this->position, intersectedPrimitive,
                                                    intersection);
    }
    return cumulativeIntensity * textureColor;
}

void Camera::printProgress(float now, float total) {
    float progress =  (now / total) * 100;
    if(fmodf(progress, 10) == 0) {
        std::cout << " - " << progress << "%\r";
        std::cout.flush();
    }
}