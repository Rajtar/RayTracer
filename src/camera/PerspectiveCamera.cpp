#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(Vector3 position, Vector3 direction, float viewportDistance, Vector3 up) : Camera(
        position, direction, viewportDistance, up) {}

Ray PerspectiveCamera::getRay(float xCenter, float yCenter) {
    return Ray(this->position, getLowerLeftCorner() + xCenter * getHorizontal() + yCenter * getVertical()- position);
}

