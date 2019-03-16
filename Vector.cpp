#include <cmath>
#include "Vector.h"

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {}

Vector::Vector(float xyz) : x(xyz), y(xyz), z(xyz) {}

Vector::~Vector() {
}

float Vector::getMagnitude() {
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vector Vector::cross(Vector other) {
    return (this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y -
                                                                                          this->y * other.x);
}

float Vector::dot(Vector other) {
    return this->x * other.x + this->y * other.y + this->z * other.z;
}

Vector Vector::operator+() {
    return *this;
}

Vector Vector::operator-() {
    return Vector(-this->x, -this->y, -this->z);
}

Vector Vector::operator+(Vector other) {
    return Vector(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector Vector::operator-(Vector other) {
    return Vector(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector Vector::operator*(float num) {
    return Vector(this->x * num, this->y * num, this->z * num);
}

Vector Vector::operator/(float num) {
    return Vector(this->x / num, this->y / y, this->z / z);
}

Vector Vector::operator*(Vector other) {
    return Vector(this->x * other.x, this->y * y, this->z * z);
}

Vector Vector::operator/(Vector other) {
    return Vector(this->x / other.x, this->y / other.y, this->z / other.z);
}

void Vector::operator+=(Vector other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
}

void Vector::operator-=(Vector other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
}

void Vector::operator*=(Vector other) {
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
}

void Vector::operator/=(Vector other) {
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
}