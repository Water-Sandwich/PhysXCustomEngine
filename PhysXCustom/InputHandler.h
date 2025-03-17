#pragma once
#include <GL/freeglut_std.h>
#include "Rect.h"
#include <vector>
#include "Listener.h"

//basis for keyboard tracking is by having an array of bools for each key state (there are 256 different keys)
//when a something checks if a key is down, itll go to the key's index in the array, and see if its true/false

namespace InputHandler {
	extern std::vector<Listener*> listeners;

	inline float mXPos, mYPos, mdy, mdx;

	bool isMouseWithin(Rect rect);

	void setup(int _gw, int _gh, int _ww, int _wh);

	//used by GLUT as callbacks
	void onKeyDown(unsigned char key, int x, int y);
	void onKeyUp(unsigned char key, int x, int y);

	void mouseEvent(int button, int state, int x, int y);
	void motionMouseEvent(int x, int y);

	bool isKeyDown(unsigned char key);
	bool isKeyUp(unsigned char key);

	bool isButtonDown(int button);
	bool isButtonUp(int button);
};