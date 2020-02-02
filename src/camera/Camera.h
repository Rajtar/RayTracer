#ifndef RENDERER_CAMERA_H
#define RENDERER_CAMERA_H

#include <memory>
#include "../geometry/Vector3.h"
#include "../Scene.h"
#include "../io/image/Image.h"
#include "../light/Light.h"

class Camera {
public:
    Vector3 position,
            direction,
            up;

    double viewportDistance;

    Camera(Vector3 position, Vector3 direction, double viewportDistance, Vector3 up = Vector3(0, 1, 0));
    Camera() = default;

    virtual void renderScene(Scene &scene, std::unique_ptr<Image> &targetImage);
    virtual Ray getRay(double xCenter, double yCenter) = 0;

private:
    virtual void renderSceneNoneAntiAliasing(const Scene &scene, std::unique_ptr<Image> &targetImage);
    virtual void renderSceneMultisapmleAntiAliasing(Scene &scene, std::unique_ptr<Image> &targetImage);
    LightIntensity calculatePixelColor(const Scene &scene,
                                       const std::shared_ptr<Primitive>& intersectedPrimitive,
                                       const Intersection &intersection);
    LightIntensity
    calculateRecursivePixelColor(Ray ray, Intersection intersection, std::shared_ptr<Primitive> intersectedPrimitive,
                                 const Scene &scene, int maxBounces);
    void printProgress(float now, float total);

    Vector3 getReflectionVector(const Ray &ray, const Intersection &intersection) const;
    Vector3 getTransmissionVector(const Ray &ray, const Intersection &intersection, float targetRefractiveIndex) const;

    Vector3 sampleRay(const Scene &scene, const Ray &ray);
};


#endif //RENDERER_CAMERA_H
