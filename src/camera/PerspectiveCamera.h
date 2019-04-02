#ifndef RENDERER_PERSPECTIVECAMERA_H
#define RENDERER_PERSPECTIVECAMERA_H


#include "Camera.h"
#include "../Scene.h"

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(Vector3 position, Vector3 direction, float viewportDistance, Vector3 up = Vector3(0, 1, 0));
    Ray getRay(float xCenter, float yCenter) override;
};


#endif //RENDERER_PERSPECTIVECAMERA_H
