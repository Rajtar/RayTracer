#include "Image.h"

Image::Image(unsigned int width, unsigned int height) : width(width), height(height) {}

Image::Image(std::string filepath) {}

unsigned int Image::getWidth() const {
    return width;
}

unsigned int Image::getHeight() const {
    return height;
}