#include "Texture.h"

Texture::Texture(const BitmapImage &textureImage) {
    this->width = textureImage.getWidth();
    this->height = textureImage.getHeight();
    for (unsigned int x = 0; x < this->width; x++) {
        for (unsigned int y = 0; y < this->height; y++) {
            this->colorMap.push_back(textureImage.readPixel(x, y));
        }
    }
}

LightIntensity Texture::getColorAt(unsigned int x, unsigned int y) const {
    return this->colorMap.at(x* this->height + y);
}

Texture::Texture() {}

int Texture::getWidth() const {
    return width;
}

int Texture::getHeight() const {
    return height;
}
