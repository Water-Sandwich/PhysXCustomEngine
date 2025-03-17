#pragma once

#include <string>
#include "Rect.h"

#define M_PI 3.14159265358979323846264338327950288

//im sure there's some external library for this but screw it
//all angles are in radians
class Vector2 {
public:
	float x, y;

	Vector2();

	Vector2(float x, float y);

	Vector2(int x, int y);

	//copy constructor
	Vector2(const Vector2& vec);

	//create a new unit vector
	Vector2 normalized() const;

	float magnitude() const;

	//returns a new vector rotated by theta radians clockwise
	Vector2 rotated(float theta) const;

	Vector2 operator+(const Vector2& a) const;

	Vector2 operator-(const Vector2& a) const;

	//multiply magnitude
	Vector2 operator*(float a) const;

	Vector2 operator/(float a) const;

	float angle(const Vector2& source = {0,0}) const;

	static Vector2 midpoint(Rect rect);

	static Vector2 randomDir();

	static float radToDeg(float num);

	static float degToRad(float num);

	static float angleTo(const Vector2& a, const Vector2& b);

	std::string toString() const;
};