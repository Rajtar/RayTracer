#ifndef RENDERER_CAMERA_H
#define RENDERER_CAMERA_H

#include <memory>
#include "geometry/Vector3.h"
#include "Scene.h"
#include "image/Image.h"

class Camera {
public:
    Vector3 position,
            target,
            up;

    float nearPlane,
            farPlane;

    Camera(Vector3 position, Vector3 target, Vector3 up, float nearPlane, float farPlane);
    Camera() = default;

    virtual void renderScene(const Scene &scene, std::unique_ptr<Image> &image) = 0;
};


#endif //RENDERER_CAMERA_H
