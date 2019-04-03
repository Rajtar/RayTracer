#ifndef RENDERER_ORTHOGRAPHICCAMERA_H
#define RENDERER_ORTHOGRAPHICCAMERA_H


#include "Camera.h"

class OrthographicCamera : public Camera {
public:
    OrthographicCamera(Vector3 position, Vector3 direction, double viewportDistance, Vector3 up = Vector3(0, 1, 0));
    Ray getRay(double xCenter, double yCenter) override;
};


#endif //RENDERER_ORTHOGRAPHICCAMERA_H
