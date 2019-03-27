#include "PerspectiveCamera.h"
#include "../geometry/Sphere.h"

PerspectiveCamera::PerspectiveCamera(Vector3 position, Vector3 direction, float viewportDistance, Vector3 up) : Camera(
        position, direction, viewportDistance, up) {}

void PerspectiveCamera::renderScene(const Scene &scene, std::unique_ptr<Image> &image) {
    unsigned int imageWidth = image->getWidth();
    unsigned int imageHeight = image->getHeight();

    float pixelHeight = 2.0F / imageWidth;
    float pixelWidth = 2.0F / imageHeight;

    for(unsigned int i = 0; i < imageWidth; i++) {
        for(unsigned int j = 0; j < imageHeight; j++) {
            float xCenter = -1.0F + (i + 0.5F) * pixelWidth;
            float yCenter = 1.0F - (j + 0.5F) * pixelHeight;

            Ray ray(this->position, Vector3(xCenter, yCenter, 0));

            std::vector<Vector3> intersections;
            for (const auto &primitive : scene.primitives) {
                if(primitive->intersect(ray, intersections)) {
                    image->writePixel(i, j, LightIntensity(1.0, 0.0, 0.0));
                }
                else {
                    image->writePixel(i, j, LightIntensity(0.0, 0.0, 0.0));
                }
            }
        }
    }
}
