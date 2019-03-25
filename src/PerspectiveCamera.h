#ifndef RENDERER_PERSPECTIVECAMERA_H
#define RENDERER_PERSPECTIVECAMERA_H


#include "Camera.h"
#include "Scene.h"

class PerspectiveCamera : public Camera {
public:
    float fov;

    PerspectiveCamera(Vector3 position, Vector3 target, Vector3 up, float nearPlane, float farPlane, float fov);

    void renderScene(const Scene &scene, std::unique_ptr<Image> &image) override;
};


#endif //RENDERER_PERSPECTIVECAMERA_H
