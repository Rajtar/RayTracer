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
    LightIntensity kA = intersectedPrimitive.get()->getAmbient();
    LightIntensity kD = intersectedPrimitive.get()->getDiffuse();
    LightIntensity kS = intersectedPrimitive.get()->getSpecular();
    double alpha = intersectedPrimitive.get()->getSmoothness();

    LightIntensity iA = this->ambientIntensity;
    LightIntensity iD = this->diffuseIntensity;
    LightIntensity iS = this->specularIntensity;

    LightIntensity ambientLight = kA * iA;

    if (!isAccessible(intersection.position, scenePrimitives)) {
        return ambientLight;
    }

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
    LightIntensity I = ambientLight + (kD * iD * (L.dot(N)) + kS * iS * pow(R.dot(V), alpha));
    return I;
}

bool PointLight::isAccessible(Vector3 reflectionPoint, std::list<std::shared_ptr<Primitive>> scenePrimitives) {
    Ray primitiveToLight(reflectionPoint, this->position);
    for (const auto &primitive : scenePrimitives) {
        std::vector<Intersection> intersections = primitive.get()->intersect(primitiveToLight);
//        if (!intersections.empty()) {
//            return false;
//        }
        for (const auto &intersection : intersections) {
            if ((reflectionPoint - intersection.position).getMagnitude() < (reflectionPoint - this->position).getMagnitude()) {
                return false;
            }
        }
    }
    return true;
}
