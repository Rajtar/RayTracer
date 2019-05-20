#ifndef RENDERER_LIGHTINTENSITY_H
#define RENDERER_LIGHTINTENSITY_H


#include <ostream>
#include "../geometry/Vector3.h"

class LightIntensity {
public:
    float r = 0,
          g = 0,
          b = 0;

    LightIntensity(float r, float g, float b);
    explicit LightIntensity(float rgb);
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
