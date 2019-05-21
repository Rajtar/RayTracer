#include <cmath>
#include "PointLight.h"

PointLight::PointLight(const LightIntensity &commonIntensity, const Vector3 &position, float constAttenuation,
                       float linearAttenuation, float quadAttenuation) : Light(commonIntensity), position(position),
                                                                         constAttenuation(constAttenuation),
                                                                         linearAttenuation(linearAttenuation),
                                                                         quadAttenuation(quadAttenuation) {}

PointLight::PointLight(const LightIntensity &diffuseIntensity, const LightIntensity &ambientIntensity,
                       const LightIntensity &specularIntensity, const Vector3 &position, float constAttenuation,
                       float linearAttenuation, float quadAttenuation) : Light(diffuseIntensity, ambientIntensity,
                                                                               specularIntensity), position(position),
                                                                         constAttenuation(constAttenuation),
                                                                         linearAttenuation(linearAttenuation),
                                                                         quadAttenuation(quadAttenuation) {}

LightIntensity
PointLight::calculateLightIntensity(std::list<std::shared_ptr<Primitive>> scenePrimitives, Vector3 cameraPosition,
                                    std::shared_ptr<Primitive> intersectedPrimitive, Vector3 intersectionPoint) {
    if(!isAccessible(intersectionPoint, scenePrimitives)) {
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
    Vector3 L = (this->position - intersectionPoint).normalized();

    // vector normal to the point on surface
    Vector3 N = intersectedPrimitive.get()->getNormalAt(intersectionPoint).normalized();

    // reflection direction vector
    //Vector3 R = L - (N * N.dot(L) * 2.0f); //werjsa z instrukcji,
    Vector3 R = (2.0f * (L.dot(N)) * N - L).normalized();

    // vector from surface to viewer
    Vector3 V = (cameraPosition - intersectionPoint).normalized();

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
        if(primitive.get()->intersect(primitiveToLight, intersections)) {
            return false;
        }
    }
    return true;
}
