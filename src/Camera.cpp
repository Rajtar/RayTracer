#include "Camera.h"

Camera::Camera(Vector3 position, Vector3 target, Vector3 up, float nearPlane, float farPlane) : position(position),
                target(target), up(up), nearPlane(nearPlane), farPlane(farPlane) {}
