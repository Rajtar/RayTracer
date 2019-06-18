#include "Primitive.h"
#include "../light/LightIntensity.h"
#include "../UUIDGenerator.h"

Primitive::Primitive() {UUID = UUIDGenerator::generateUUID();}

Primitive::Primitive(Material material) : material(material) {UUID = UUIDGenerator::generateUUID();}

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

const std::string &Primitive::getUUID() const {
    return UUID;
}

bool operator==(const Primitive &lhs, const Primitive &rhs) {
    return lhs.getUUID() == rhs.getUUID();
}

bool operator!=(const Primitive &lhs, const Primitive &rhs) {
    return !(lhs.getUUID() == rhs.getUUID());
}
