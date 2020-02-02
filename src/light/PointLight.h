//
// Created by jakub on 20.05.2019.
//

#ifndef RENDERER_POINTLIGHT_H
#define RENDERER_POINTLIGHT_H


#include "Light.h"

class PointLight : public Light {
public:
    Vector3 position = Vector3(0);

    PointLight(const LightIntensity &commonIntensity, const Vector3 &position);

    PointLight(const LightIntensity &diffuseIntensity, const LightIntensity &ambientIntensity,
                   const LightIntensity &specularIntensity, const Vector3 &position);

    LightIntensity
    calculateLightIntensity(std::vector<std::shared_ptr<Primitive>> scenePrimitives, Vector3 cameraPosition,
                            const Primitive &intersectedPrimitive, Intersection intersection) override;

    bool isAccessible(Vector3 reflectionPoint, const Primitive &intersectedPrimitive,
                      std::vector<std::shared_ptr<Primitive>> scenePrimitives) override;
};


#endif //RENDERER_POINTLIGHT_H
