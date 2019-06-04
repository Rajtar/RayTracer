#include "Primitive.h"
#include "../light/LightIntensity.h"

Primitive::Primitive(Material material) : material(material) {}

LightIntensity Primitive::getDiffuse() const {
    return material.diffuse;
}

LightIntensity Primitive::getAmbient() const {
    return material.ambient;
}

LightIntensity Primitive::getSpecular() const {
    return material.specular;
}

double Primitive::getSmoothness() const {
    return material.smoothness;
}

void
Primitive::getTexelCoordinates(const Vector3 &intersection, const int textureWidth, const int textureHeight, int &row,
                               int &column) const {
//TODO: Make abstract
}
