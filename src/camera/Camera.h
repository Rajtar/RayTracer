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

    virtual void renderScene(const Scene &scene, std::unique_ptr<Image> &targetImage);
    virtual Ray getRay(double xCenter, double yCenter) = 0;

private:
    virtual void renderSceneNoneAntiAliasing(const Scene &scene, std::unique_ptr<Image> &targetImage);
    virtual void renderSceneMultisapmleAntiAliasing(const Scene &scene, std::unique_ptr<Image> &targetImage);
    LightIntensity calculatePixelColor(Scene scene,
                                       std::shared_ptr<Primitive> intersectedPrimitive,
                                       Intersection intersection);
    LightIntensity calculateReflectivePixelColor(Ray ray, Intersection intersection, const Scene &scene, int maxBounces);
    void printProgress(float now, float total);
};


#endif //RENDERER_CAMERA_H
