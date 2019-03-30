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
            viewportDistance,
            up;

    Camera(Vector3 position, Vector3 direction, float viewportDistance, Vector3 up = Vector3());
    Camera() = default;

    virtual void renderScene(const Scene &scene, std::unique_ptr<Image> &targetImage) = 0;
};


#endif //RENDERER_CAMERA_H