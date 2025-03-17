#include <cmath>

#include "Vector2.h"
#include "Rect.h"

Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::Vector2(float _x, float _y) {
	x = _x;
	y = _y;
}

Vector2::Vector2(int _x, int _y) {
	x = (float)_x;
	y = (float)_y;
}

Vector2::Vector2(const Vector2& vec) {
	x = vec.x;
	y = vec.y;
}

Vector2 Vector2::normalized() const {
	const float mag = magnitude();
	return {x / mag, y / mag};
}

float Vector2::magnitude() const {
	//pythagorean theorem used
	return std::sqrt(x * x + y * y);
}

Vector2 Vector2::rotated(float theta) const {
	return {cos(theta) * x - sin(theta) * y,
			sin(theta) * x + cos(theta) * y};
}

Vector2 Vector2::operator+(const Vector2& a) const {
	return {x + a.x, y + a.y};
}

Vector2 Vector2::operator-(const Vector2& a) const {
	return {x - a.x, y - a.y};
}

Vector2 Vector2::operator*(float a) const {
	return {x * a, y * a};
}

Vector2 Vector2::operator/(float a) const {
	return {x / a, y / a};
}

float Vector2::radToDeg(float num) {
	return (float)(num * (180.0 / M_PI));
}

float Vector2::degToRad(float num) {
	return num * M_PI / 180;
}

float Vector2::angleTo(const Vector2& a, const Vector2& b) {
	Vector2 proc = {b.x - a.x, b.y - a.y};
	return atan2(proc.y, proc.x);
	//float ang = atan2(proc.y, proc.x);
	//Vector2 unit = { cos(ang), sin(ang) };
}

Vector2 Vector2::midpoint(Rect rect) {
	return {rect.x + rect.w / 2, rect.y + rect.h / 2};
}

Vector2 Vector2::randomDir() {
	return Vector2(rand() % 1001 - 500, rand() % 1001 - 500).normalized();
}

std::string Vector2::toString() const {
	return std::to_string(x) + ", " + std::to_string(y);
}

float Vector2::angle(const Vector2& source) const {
	return angleTo(source, {x, y});
}


