#ifndef RENDERER_BITMAPIMAGE_H
#define RENDERER_BITMAPIMAGE_H

#include "bitmap_image.hpp"
#include "../../light/LightIntensity.h"
#include "Image.h"

class BitmapImage : public Image {
public:
    BitmapImage(unsigned int width, unsigned int height);
    explicit BitmapImage(std::string filepath);

    void saveToFile(const std::string &filename) override;
    LightIntensity readPixel(unsigned int x, unsigned int y) const override;
    void writePixel(unsigned int x, unsigned int y, const LightIntensity& intensity) override;
    void writePixel(unsigned int x, unsigned int y, unsigned char red, unsigned char green, unsigned char blue) override;
    void writeAll(const LightIntensity& intensity) override;
    void writeAll(unsigned char red, unsigned char green, unsigned char blue) override;

    unsigned int getWidth() const override;
    unsigned int getHeight() const override;

private:
    bitmap_image data;
};


#endif //RENDERER_BITMAPIMAGE_H
