#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(Vector3 position, Vector3 target, Vector3 up, float nearPlane, float farPlane,
                                        float fov) : Camera(position, target, up, nearPlane, farPlane), fov(fov) {}

void PerspectiveCamera::renderScene(const Scene &scene, std::unique_ptr<Image> &image) {
    unsigned int imageWidth = image->getWidth();
    unsigned int imageHeight = image->getHeight();

    for(int i = 0; i < imageWidth; i++) {
        for(int j = 0; j < imageHeight; j++) {
            int xCenter = -1 + (i + 0.5) * 2 / imageWidth;
            int yCenter = 1 - (i + 0.5) * 2 / imageHeight;

            Ray ray(this->position, Vector3(xCenter, yCenter, 0));

            std::vector<Vector3> intersections;
            for(Primitive primitive : scene.primitives) {
                if(primitive.intersect(ray, intersections)) {
                    image->writePixel(i, j, LightIntensity(1.0, 0.0, 0.0));
                }
                else {
                    image->writePixel(i, j, LightIntensity(0.0, 0.0, 0.0));
                }
            }
        }
    }
}
