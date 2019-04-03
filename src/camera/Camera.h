#ifndef RENDERER_CAMERA_H
#define RENDERER_CAMERA_H

#include <memory>
#include "../geometry/Vector3.h"
#include "../Scene.h"
#include "../image/Image.h"

class Camera {
public:
    Vector3 position,
            direction,
            up;

    float viewportDistance;

    Camera(Vector3 position, Vector3 direction, float viewportDistance, Vector3 up = Vector3(0, 1, 0));
    Camera() = default;

    virtual void renderScene(const Scene &scene, std::unique_ptr<Image> &targetImage);
    virtual Ray getRay(float xCenter, float yCenter) = 0;

    const Vector3 &getLowerLeftCorner() const;

    void setLowerLeftCorner(const Vector3 &lowerLeftCorner);

    const Vector3 &getHorizontal() const;

    void setHorizontal(const Vector3 &horizontal);

    const Vector3 &getVertical() const;

    void setVertical(const Vector3 &vertical);

private:
    Vector3 u, v, w;
    Vector3 lowerLeftCorner;
    Vector3 horizontal;
    Vector3 vertical;
};


#endif //RENDERER_CAMERA_H
