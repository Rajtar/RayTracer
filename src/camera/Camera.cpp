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
                    Intersection currentIntersection = intersections.front();
                    double intersectionDepth = (position - currentIntersection.position).getMagnitude();
                    if(intersectionDepth < lowestPixelDepth) {
                        lowestPixelDepth = intersectionDepth;

                        if(primitive->material.type == Reflective || primitive->material.type == Refractive ){

                            pixelColor = calculateRecursivePixelColor(ray, currentIntersection,
                                                                      primitive, scene, 10);
                        }
                        else {
                            pixelColor = calculatePixelColor(scene, primitive, currentIntersection);
                        }
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
                            LightIntensity calculatedColor;
                            if(primitive->material.type != Default){
                                calculatedColor = calculateRecursivePixelColor(ray, intersections.front(),
                                                                               primitive, scene, 3);
                            }
                            else {
                                calculatedColor = calculatePixelColor(scene, primitive, intersections.front());
                            }
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

LightIntensity Camera::calculatePixelColor(const Scene &scene,
                                           std::shared_ptr<Primitive> intersectedPrimitive,
                                           Intersection intersection) {
        int textureX, textureY;
        Texture &objectTexture = intersectedPrimitive->material.texture;
        LightIntensity textureColor(1, 1, 1);

        if (!objectTexture.isEmpty()) {
            intersectedPrimitive->getTexelCoordinates(intersection.position, objectTexture.getWidth(),
                                                      objectTexture.getHeight(), textureX, textureY);
            textureColor = objectTexture.getColorAt(textureX, textureY);
        }

        LightIntensity cumulativeIntensity;
        for (const auto &light : scene.lights) {
            cumulativeIntensity += light.get()->calculateLightIntensity(scene.primitives, this->position,
                                                                        intersectedPrimitive,
                                                                        intersection);
        }
        return cumulativeIntensity * textureColor;
}

LightIntensity
Camera::calculateRecursivePixelColor(Ray ray, Intersection intersection,
                                     std::shared_ptr<Primitive> intersectedPrimitive,
                                     const Scene &scene, int maxBounces) {
    LightIntensity pixelColor = LightIntensity(0, 0, 1);
    int i = 0;
    bool bounceAllowed = true;
    std::shared_ptr<Primitive> lastHitPrimitive;
    Intersection lastIntersection;

    while(bounceAllowed && i < maxBounces) {
        Vector3 bounceDirection;
        if(intersectedPrimitive->material.type == Reflective) {
            bounceDirection = getReflectionVector(ray, intersection);
        } else if(intersectedPrimitive->material.type == Refractive) {
            bounceDirection = getTransmissionVector(ray, intersection, intersectedPrimitive->material.refractiveIndex);
        }
        ray = Ray(intersection.position, intersection.position + bounceDirection);
        double lowestPixelDepth = std::numeric_limits<double>::max();

        for (const auto &primitive : scene.primitives) {
            if(primitive->compareUUID(*intersectedPrimitive) && primitive->material.type != Refractive) {
                continue;
            }
            std::vector<Intersection> intersections = primitive->intersect(ray);
            if (!intersections.empty()) {
                Intersection currentIntersection = primitive->material.type == Refractive ? intersections.back() : intersections.front();

                float intersectionDistance = (intersection.position - currentIntersection.position).getMagnitude();
                if (fabs(intersectionDistance) < 0.1) {
                    continue;
                }

                double intersectionDepth = (intersection.position - currentIntersection.position).getMagnitude();
                if(intersectionDepth < lowestPixelDepth) {
                    lowestPixelDepth = intersectionDepth;
                    lastIntersection = currentIntersection;
                    lastHitPrimitive = primitive;
                    bounceAllowed = primitive->material.type == Reflective || primitive->material.type == Refractive;
                }
            }
        }
        i++;
        intersection = lastIntersection;
    }
    if(lastHitPrimitive != nullptr) {
        pixelColor = calculatePixelColor(scene, lastHitPrimitive, intersection);
    }
    return pixelColor;
}

Vector3 Camera::getReflectionVector(const Ray &ray, const Intersection &intersection) const {
    Vector3 bounceDirection = ray.direction - (2 * ray.direction.dot(intersection.normal) * intersection.normal);
    return bounceDirection;
}

Vector3
Camera::getTransmissionVector(const Ray &ray, const Intersection &intersection, float targetRefractiveIndex) const {
    float cosI = ray.direction.dot(intersection.normal);
    cosI = std::min(cosI, 1.0f);
    cosI = std::max(cosI, -1.0f);

    float originRefractiveIndex = 1;
    Vector3 normal = intersection.normal;

    if(cosI < 0)
    {
        cosI = -cosI;
    }
    else
    {
        std::swap(originRefractiveIndex, targetRefractiveIndex);
        normal = -intersection.normal;
    }

    float eta = originRefractiveIndex / targetRefractiveIndex;
    float k = 1 - eta * eta * (1 - cosI * cosI);
    return k < 0 ? 0 : eta * ray.direction + (eta * cosI - sqrtf(k)) * normal;
}

void Camera::printProgress(float now, float total) {
    float progress =  (now / total) * 100;
    if(fmodf(progress, 10) == 0) {
        std::cout << " - " << progress << "%\r";
        std::cout.flush();
    }
}


