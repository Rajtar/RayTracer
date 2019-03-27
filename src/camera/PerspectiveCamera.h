#ifndef RENDERER_PERSPECTIVECAMERA_H
#define RENDERER_PERSPECTIVECAMERA_H


#include "Camera.h"
#include "../Scene.h"

class PerspectiveCamera : public Camera {
public:
    float fov;

    PerspectiveCamera(Vector3 position, Vector3 direction, float viewportDistance, Vector3 up = Vector3(0, 1, 0));

    void renderScene(const Scene &scene, std::unique_ptr<Image> &image) override;
};


#endif //RENDERER_PERSPECTIVECAMERA_H
