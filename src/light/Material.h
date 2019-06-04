#ifndef RENDERER_MATERIAL_H
#define RENDERER_MATERIAL_H


#include "LightIntensity.h"
#include "Texture.h"

class Material {
public:
    Texture texture;

    LightIntensity diffuse, ambient, specular;
    double smoothness;

    Material() = default;
    Material(const LightIntensity &diffuse, const LightIntensity &ambient, const LightIntensity &specular,
             double smoothness);
    Material(const Texture &texture, const LightIntensity &diffuse, const LightIntensity &ambient,
             const LightIntensity &specular, double smoothness);
};


#endif //RENDERER_MATERIAL_H
