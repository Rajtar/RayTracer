#include "BitmapImage.h"

BitmapImage::BitmapImage(const unsigned int width, const unsigned int height) : Image(width, height) {
    this->data = bitmap_image(width, height);
}

BitmapImage::BitmapImage(std::string filepath) : Image(filepath) {
    this->data = bitmap_image(filepath);
}

void BitmapImage::saveToFile(const std::string &filename) {
    this->data.save_image(filename);
}

LightIntensity BitmapImage::readPixel(unsigned int x, unsigned int y) {
    rgb color = this->data.get_pixel(x, y);
    return LightIntensity(color.red / 255.0F, color.green / 255.0F, color.blue / 255.0F);
}

void BitmapImage::writePixel(unsigned int x, unsigned int y, const LightIntensity &intensity) {
    rgb color = rgb(intensity.r *255, intensity.g * 255, intensity.b * 255);
    this->data.set_pixel(x, y, color);
}

void BitmapImage::writePixel(unsigned int x, unsigned int y, const unsigned char red, const unsigned char green,
                       const unsigned char blue) {
    this->data.set_pixel(x, y, red, green, blue);
}

void BitmapImage::writeAll(const LightIntensity &intensity) {
    this->data.set_all_channels(intensity.r * 255, intensity.g * 255, intensity.b * 255);
}

void BitmapImage::writeAll(unsigned char red, unsigned char green, unsigned char blue) {
    this->data.set_all_channels(red, green, blue);
}

unsigned int BitmapImage::getWidth() {
    return data.width();
}

unsigned int BitmapImage::getHeight() {
    return data.height();
}
