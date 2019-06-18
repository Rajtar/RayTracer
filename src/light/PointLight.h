//
// Created by jakub on 20.05.2019.
//

#ifndef RENDERER_POINTLIGHT_H
#define RENDERER_POINTLIGHT_H


#include "Light.h"

class PointLight : public Light {
public:
    Vector3 position;

    PointLight(const LightIntensity &commonIntensity, const Vector3 &position);

    PointLight(const LightIntensity &diffuseIntensity, const LightIntensity &ambientIntensity,
                   const LightIntensity &specularIntensity, const Vector3 &position);

    LightIntensity
    calculateLightIntensity(std::list<std::shared_ptr<Primitive>> scenePrimitives, Vector3 cameraPosition,
                            std::shared_ptr<Primitive> intersectedPrimitive, Intersection intersection) override;

    bool isAccessible(Vector3 reflectionPoint, std::shared_ptr<Primitive> intersectedPrimitive,
                      std::list<std::shared_ptr<Primitive>> scenePrimitives) override;
};


#endif //RENDERER_POINTLIGHT_H
