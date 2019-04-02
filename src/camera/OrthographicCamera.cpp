#include "OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(Vector3 position, Vector3 direction, float viewportDistance, Vector3 up)
        : Camera(position, direction, viewportDistance, up) {

}

Ray OrthographicCamera::getRay(float xCenter, float yCenter) {
    return Ray(Vector3(xCenter, yCenter, position.z), Vector3(xCenter, yCenter, viewportDistance));
}
