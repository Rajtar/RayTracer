#include <limits>
#include <cmath>
#include "Camera.h"
#include "../static/Settings.hpp"

Camera::Camera(Vector3 position, Vector3 direction, double viewportDistance, Vector3 up) : position(position),
                                                                                          direction(direction),
                                                                                          viewportDistance(viewportDistance),
                                                                                          up(up) {}

void Camera::renderScene(const Scene &scene, std::unique_ptr<Image> &targetImage) {
    unsigned int imageWidth = targetImage->getWidth();
    unsigned int imageHeight = targetImage->getHeight();

    double pixelHeight = 2.0F / imageWidth;
    double pixelWidth = 2.0F / imageHeight;

    if(Settings::AntialiasingType == None) {
        for (unsigned int x = 0; x < imageWidth; x++) {
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
                        double intersectionDepth = (position - intersections.at(0)).getMagnitude();
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
                        getRay(xCenter, yCenter),
                        getRay(xUpperLeft, yUpperLeft),
                        getRay(xLowerLeft, yLowerLeft),
                        getRay(xUpperRight, yUpperRight),
                        getRay(xLowerRight, yLowerRight),
                };

                std::vector<Vector3> intersections;
                int i = 0;
                Vector3 previousColor;
                for (const auto &primitive : scene.primitives) {
                    Vector3 lightIntensity(0, 0, 0);
                    for (const auto &ray : rays) {
                        if (primitive->intersect(ray, intersections)) {
                            lightIntensity += Vector3((float) x / imageWidth, (float) i / scene.primitives.size() , (float) y / imageHeight);
                        } else {
                            lightIntensity += previousColor;
                        }
                    }

                    lightIntensity /= 5;
                    if(lightIntensity.x != 0 || lightIntensity.y != 0 || lightIntensity.z != 0) {
                        targetImage->writePixel(x, y, LightIntensity(lightIntensity.x, lightIntensity.y, lightIntensity.z));
                    }
                    previousColor = Vector3(lightIntensity.x, lightIntensity.y, lightIntensity.z);
                    i++;
                }
            }
        }
    }
}
