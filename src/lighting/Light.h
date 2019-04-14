#ifndef RENDERER_LIGHT_H
#define RENDERER_LIGHT_H


#include "../LightIntensity.h"

class Light {
public:
    LightIntensity color;

    Light(LightIntensity color) : color(color);
    Light() = 0;
};


#endif //RENDERER_LIGHT_H
