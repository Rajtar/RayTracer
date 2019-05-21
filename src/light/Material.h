#ifndef RENDERER_MATERIAL_H
#define RENDERER_MATERIAL_H


#include "LightIntensity.h"

class Material {
public:
    LightIntensity diffuse, ambient, specular;
    double smoothness;

    Material(const LightIntensity &diffuse, const LightIntensity &ambient, const LightIntensity &specular,
             double smoothness);
    Material() = default;
};


#endif //RENDERER_MATERIAL_H
