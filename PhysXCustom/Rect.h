#pragma once
#include <stdio.h>

struct Rect {
	float x, y, w, h;

	//checks if point (_x,_y) is within this rectangle
	bool withinBounds(float _x, float _y) {
		return (x < _x && _x < (x + w)) && (_y > y && _y < (y+h));
	}
};