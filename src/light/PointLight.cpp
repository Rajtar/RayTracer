#include <cmath>
#include "PointLight.h"

PointLight::PointLight(const LightIntensity &commonIntensity, const Vector3 &position)
        : Light(commonIntensity), position(position) {}

PointLight::PointLight(const LightIntensity &diffuseIntensity, const LightIntensity &ambientIntensity,
                       const LightIntensity &specularIntensity, const Vector3 &position) : Light(diffuseIntensity,
                                                                                                 ambientIntensity,
                                                                                                 specularIntensity),
                                                                                           position(position) {}

LightIntensity PointLight::calculateLightIntensity(std::list<std::shared_ptr<Primitive>> scenePrimitives,
                                                   Vector3 cameraPosition,
                                                   std::shared_ptr<Primitive> intersectedPrimitive,
                                                   Intersection intersection) {
    if (!isAccessible(intersection.position, scenePrimitives)) {
        return LightIntensity(0, 0, 0);
    }

    LightIntensity kA = intersectedPrimitive.get()->getAmbient();
    LightIntensity kD = intersectedPrimitive.get()->getDiffuse();
    LightIntensity kS = intersectedPrimitive.get()->getSpecular();
    double alpha = intersectedPrimitive.get()->getSmoothness();

    LightIntensity iA = this->ambientIntensity;
    LightIntensity iD = this->diffuseIntensity;
    LightIntensity iS = this->specularIntensity;

    // direction vector from the point on the surface toward light source
    Vector3 L = (this->position - intersection.position).normalized();

    // vector normal to the point on surface
    Vector3 N = intersection.normal.normalized();

    // reflection direction vector
    Vector3 R = (2.0f * (L.dot(N)) * N - L).normalized();

    // vector from surface to viewer
    Vector3 V = (cameraPosition - intersection.position).normalized();

    //TODO: move ambient light so it will calculate once for all light sources

    //Phong equation
    LightIntensity I = kA * iA + (kD * iD * (L.dot(N)) + kS * iS * pow(R.dot(V), alpha));
//    double distance = (this->position - intersectionPoint).getMagnitude() / 100.0;
//    LightIntensity attenuatedI = LightIntensity(I.r / distance, I.g / distance, I.b / distance);
    return I;
}

bool PointLight::isAccessible(Vector3 reflectionPoint, std::list<std::shared_ptr<Primitive>> scenePrimitives) {
    Ray primitiveToLight(reflectionPoint, this->position);
    std::vector<Vector3> intersections;
    for (const auto &primitive : scenePrimitives) {
        if (!primitive.get()->intersect(primitiveToLight).empty()) {
            return false;
        }
    }
    return true;
}
