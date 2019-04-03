#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(Vector3 position, Vector3 direction, double viewportDistance, Vector3 up) : Camera(
        position, direction, viewportDistance, up) {}

Ray PerspectiveCamera::getRay(double xCenter, double yCenter) {
    return Ray(this->position, Vector3(xCenter, yCenter, viewportDistance));
}

