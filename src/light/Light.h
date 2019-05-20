#ifndef RENDERER_LIGHT_H
#define RENDERER_LIGHT_H


#include "LightIntensity.h"

class Light {
public:
    LightIntensity color;

    Light(LightIntensity color);
    Light() = default;

    virtual ~Light() = 0 ;
};




#endif //RENDERER_LIGHT_H
