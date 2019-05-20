#ifndef RENDERER_MATERIAL_H
#define RENDERER_MATERIAL_H


#include "LightIntensity.h"

class Material {
public:
    LightIntensity diffuse, ambient, specular, transmition;
    float smoothness;

    Material(const LightIntensity &diffuse, const LightIntensity &ambient, const LightIntensity &specular, const LightIntensity &transmition);
    Material() = default;
};


#endif //RENDERER_MATERIAL_H
