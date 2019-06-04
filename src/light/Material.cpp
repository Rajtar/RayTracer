#include "Material.h"

Material::Material(const LightIntensity &diffuse, const LightIntensity &ambient, const LightIntensity &specular,
                   double smoothness)
        : diffuse(diffuse), ambient(ambient), specular(specular), smoothness(smoothness) {}

Material::Material(const Texture &texture, const LightIntensity &diffuse, const LightIntensity &ambient,
                   const LightIntensity &specular, double smoothness) : texture(texture), diffuse(diffuse),
                                                                        ambient(ambient), specular(specular),
                                                                        smoothness(smoothness) {}
