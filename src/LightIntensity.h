#ifndef RENDERER_LIGHTINTENSITY_H
#define RENDERER_LIGHTINTENSITY_H


class LightIntensity {
public:
    float r, g, b;

    LightIntensity(float r, float g, float b);
    LightIntensity(float rgb);
    LightIntensity() = default;
};


#endif //RENDERER_LIGHTINTENSITY_H
