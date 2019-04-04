#ifndef RENDERER_CAMERA_H
#define RENDERER_CAMERA_H

#include <memory>
#include "../geometry/Vector3.h"
#include "../Scene.h"
#include "../image/Image.h"

class Camera {
public:
    Vector3 position,
            direction,
            up;

    float viewportDistance;

    Camera(Vector3 position, Vector3 direction, double viewportDistance, Vector3 up = Vector3(0, 1, 0));
    Camera() = default;

    virtual void renderScene(const Scene &scene, std::unique_ptr<Image> &targetImage);
    virtual Ray getRay(double xCenter, double yCenter) = 0;

private:
    virtual void renderSceneNoneAntialiasing(const Scene &scene, std::unique_ptr<Image> &targetImage);
    virtual void renderSceneMultisapmleAntialiasing(const Scene &scene, std::unique_ptr<Image> &targetImage);
};


#endif //RENDERER_CAMERA_H
