#include "Camera.h"

Camera::Camera(Vector3 position, Vector3 direction, float viewportDistance, Vector3 up) : position(position),
                                                                                          direction(direction),
                                                                                          viewportDistance(viewportDistance),
                                                                                          up(up) {}
