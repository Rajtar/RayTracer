#ifndef RENDERER_CAMERA_H
#define RENDERER_CAMERA_H

#include <memory>
#include "../geometry/Vector3.h"
#include "../Scene.h"
#include "../io/image/Image.h"
#include "../light/Light.h"

class Camera {
public:
    Vector3 position = Vector3(0),
            direction = Vector3(0),
            up = Vector3(0);

    double viewportDistance = 0;

    Camera(Vector3 position, Vector3 direction, double viewportDistance, Vector3 up = Vector3(0, 1, 0));

    Camera() = default;

    virtual void renderScene(Scene &scene, Image &targetImage);

    virtual Ray getRay(double xCenter, double yCenter) = 0;

private:
    virtual void renderSceneNoneAntiAliasing(const Scene &scene, Image &targetImage);

    virtual void renderSceneMultisampleAntiAliasing(Scene &scene, Image &targetImage);

    Vector3 sampleRay(const Scene &scene, const Ray &ray);

    LightIntensity calculatePixelColor(const Scene &scene,
                                       const Primitive &intersectedPrimitive,
                                       const Intersection &intersection);

    LightIntensity calculateRecursivePixelColor(Ray ray, Intersection intersection,
                                                const Primitive &intersectedPrimitive, const Scene &scene,
                                                int maxBounces);

    Vector3 getReflectionVector(const Ray &ray, const Intersection &intersection) const;

    Vector3 getTransmissionVector(const Ray &ray, const Intersection &intersection, float targetRefractiveIndex) const;

    void printProgress(float now, float total);
};


#endif //RENDERER_CAMERA_H
