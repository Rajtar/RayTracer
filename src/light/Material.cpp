#include "Material.h"

Material::Material(const LightIntensity &diffuse, const LightIntensity &ambient, const LightIntensity &specular, const LightIntensity &transmition)
        : diffuse(diffuse), ambient(ambient), specular(specular), transmition(transmition) {}
