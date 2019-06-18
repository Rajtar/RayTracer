#include "Material.h"

Material::Material(const LightIntensity &diffuse, const LightIntensity &ambient, const LightIntensity &specular,
                   double smoothness, double refractiveIndex, MaterialTypes type)
        : diffuse(diffuse), ambient(ambient), specular(specular), smoothness(smoothness),
        refractiveIndex(refractiveIndex), type(type) {}

Material::Material(const Texture &texture, const LightIntensity &diffuse, const LightIntensity &ambient,
                   const LightIntensity &specular, double smoothness, double refractiveIndex, MaterialTypes type) : texture(texture), diffuse(diffuse),
                                                                        ambient(ambient), specular(specular),
                                                                        smoothness(smoothness), refractiveIndex(refractiveIndex), type(type) {}