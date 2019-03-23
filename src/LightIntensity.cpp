#include "LightIntensity.h"

LightIntensity::LightIntensity(float r, float g, float b) : r(r), g(g), b(b) {}

LightIntensity::LightIntensity(float rgb) : r(rgb), g(rgb), b(rgb) {}

//region InstanceOperators

void LightIntensity::operator+=(const LightIntensity &other) {
    this->r = std::min(this->r + other.r, 1.0F);
    this->g = std::min(this->g + other.g, 1.0F);
    this->b = std::min(this->b + other.b, 1.0F);
}

void LightIntensity::operator-=(const LightIntensity &other) {
    this->r = std::max(this->r - other.r, 0.0F);
    this->g = std::max(this->g - other.g, 0.0F);
    this->b = std::max(this->b - other.b, 0.0F);
}

void LightIntensity::operator*=(const LightIntensity &other) {
    this->r *= other.r;
    this->g *= other.g;
    this->b *= other.b;
}

void LightIntensity::operator/=(const LightIntensity &other) {
    this->r = std::min(this->r / other.r, 1.0F);
    this->g = std::min(this->g / other.g, 1.0F);
    this->b = std::min(this->b / other.b, 1.0F);
}
//endregion

//region GeneralOperators

LightIntensity operator+(const LightIntensity &left, const LightIntensity &right) {
    return LightIntensity(std::min(left.r + right.r, 1.0F),
                          std::min(left.g + right.g, 1.0F),
                          std::min(left.b + right.b, 1.0F));
}

LightIntensity operator-(const LightIntensity &left, const LightIntensity &right) {
    return LightIntensity(std::max(left.r - right.r, 0.0F),
                          std::max(left.g - right.g, 0.0F),
                          std::max(left.b - right.b, 0.0F));
}

LightIntensity operator*(const LightIntensity &left, const LightIntensity &right) {
    return LightIntensity(left.r * right.r, left.g * right.g, left.b * right.b);
}

LightIntensity operator/(const LightIntensity &left, const LightIntensity &right) {
    return LightIntensity(std::min(left.r / right.r, 1.0F),
                          std::min(left.g / right.g, 1.0F),
                          std::min(left.b / right.b, 1.0F));
}

std::ostream &operator<<(std::ostream &os, const LightIntensity &intensity) {
    return os << "[R: " << intensity.r << ", G: " << intensity.g << ", B: " << intensity.b << "]";
}
//endregion
