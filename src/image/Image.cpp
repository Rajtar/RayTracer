#include "Image.h"

Image::Image(unsigned int width, unsigned int height) : width(width), height(height) {}

unsigned int Image::getWidth() {
    return width;
}

unsigned int Image::getHeight() {
    return height;
}
