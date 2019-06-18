#ifndef RENDERER_MATERIAL_H
#define RENDERER_MATERIAL_H

#include "LightIntensity.h"
#include "Texture.h"

enum MaterialTypes {
    Default = 0,
    Reflective = 1,
    Refractive = 2
};

class Material {
public:
    Texture texture;
    MaterialTypes type = Default;
    LightIntensity diffuse, ambient, specular;
    double smoothness;
    double refractiveIndex = 1;

    Material() = default;
    Material(const LightIntensity &diffuse, const LightIntensity &ambient, const LightIntensity &specular,
             double smoothness, double refractiveIndex = 1, MaterialTypes type = Default);
    Material(const Texture &texture, const LightIntensity &diffuse, const LightIntensity &ambient,
             const LightIntensity &specular, double smoothness, double refractiveIndex = 1, MaterialTypes type = Default);
};


#endif //RENDERER_MATERIAL_H
