#ifndef RENDERER_LIGHTINTENSITY_H
#define RENDERER_LIGHTINTENSITY_H


#include <ostream>

class LightIntensity {
public:
    float r, g, b;

    LightIntensity(float r, float g, float b);
    LightIntensity(float rgb);
    LightIntensity() = default;

    void operator+=(const LightIntensity &other);
    void operator-=(const LightIntensity &other);
    void operator*=(const LightIntensity &other);
    void operator/=(const LightIntensity &other);
};

LightIntensity operator+(const LightIntensity &left, const LightIntensity &right);
LightIntensity operator-(const LightIntensity &left, const LightIntensity &right);
LightIntensity operator*(const LightIntensity &left, const LightIntensity &right);
LightIntensity operator/(const LightIntensity &left, const LightIntensity &right);
std::ostream& operator<<(std::ostream &os, const LightIntensity& intensity);


#endif //RENDERER_LIGHTINTENSITY_H
