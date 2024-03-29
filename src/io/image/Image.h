#ifndef RENDERER_IMAGE_H
#define RENDERER_IMAGE_H


#include <string>
#include "../../light/LightIntensity.h"

class Image {
private:
    unsigned int width, height;
public:
    Image(unsigned int width, unsigned int height);
    Image(std::string filepath);

    virtual unsigned int getWidth() const;
    virtual unsigned int getHeight() const;

    virtual void saveToFile(const std::string &filename) = 0;
    virtual LightIntensity readPixel(unsigned int x, unsigned int y) const = 0;
    virtual void writePixel(unsigned int x, unsigned int y, const LightIntensity& intensity) = 0;
    virtual void writePixel(unsigned int x, unsigned int y, unsigned char red, unsigned char green, unsigned char blue) = 0;
    virtual void writeAll(const LightIntensity& intensity) = 0;
    virtual void writeAll(unsigned char red, unsigned char green, unsigned char blue) = 0;
};


#endif //RENDERER_IMAGE_H
