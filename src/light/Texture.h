#ifndef RENDERER_TEXTURE_H
#define RENDERER_TEXTURE_H


#include "LightIntensity.h"
#include "../io/image/Image.h"
#include "../io/image/BitmapImage.h"
#include <vector>

class Texture {
public:
    explicit Texture(const BitmapImage &textureImage);
    Texture();

    LightIntensity getColorAt(unsigned int x, unsigned int y) const;

    int getWidth() const;

    int getHeight() const;

private:
    int width, height;
    std::vector<LightIntensity> colorMap;
};


#endif //RENDERER_TEXTURE_H
