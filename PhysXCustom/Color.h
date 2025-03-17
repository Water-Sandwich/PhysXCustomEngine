#pragma once
#include <stdlib.h>

struct Color {
	float r, g, b;

	//returns a new random color
	//has to be inline as this is defined within a .h file instead of .cpp, sometimes can cause issues without inline
	inline static Color random() {
		Color c{};
		c.r = (rand() % 1001) / 1000.f;
		c.g = (rand() % 1001) / 1000.f;
		c.b = (rand() % 1001) / 1000.f;
		return c;
	}
};