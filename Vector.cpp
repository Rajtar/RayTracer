#include <cmath>
#include "Vector.h"

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {}

Vector::Vector(float xyz) : x(xyz), y(xyz), z(xyz) {}

Vector::Vector(const Vector &p1, const Vector &p2) {
    this->x = p2.x - p1.x;
    this->y = p2.y - p1.y;
    this->z = p2.z - p1.z;
}

Vector::~Vector() {
}

float Vector::getMagnitude() {
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void Vector::normalize() {
    float magnitude = getMagnitude();
    if(magnitude != 0) {
        *this /= magnitude;
    }
}

Vector Vector::cross(Vector other) {
    return (this->y * other.z - this->z * other.y, this->z * other.x - this->x * other.z, this->x * other.y -
                                                                                          this->y * other.x);
}

float Vector::dot(Vector other) {
    return this->x * other.x + this->y * other.y + this->z * other.z;
}

//region InstanceOperators

Vector Vector::operator+() {
    return *this;
}

Vector Vector::operator-() {
    return Vector(-this->x, -this->y, -this->z);
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

//endregion

//region GeneralOperators

Vector operator+(Vector left, Vector right) {
    return Vector(left.x + right.x, left.y + right.y, left.z + right.z);
}

Vector operator-(Vector left, Vector right) {
    return Vector(left.x - right.x, left.y - right.y, left.z - right.z);
}

Vector operator*(Vector left, Vector right) {
    return Vector(left.x * right.x, left.y * right.y, left.z * right.z);
}

Vector operator/(Vector left, Vector right) {
    return Vector(left.x / right.x, left.y / right.y, left.z / right.z);
}

std::ostream& operator<<(std::ostream &os, const Vector& vector) {
    return os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
}
//endregion