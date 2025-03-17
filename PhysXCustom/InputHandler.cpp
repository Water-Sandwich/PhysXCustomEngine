#include <cstring>
#include <GL/freeglut_std.h>

#include "InputHandler.h"
#include "Game.h"
#include "MouseState.h"

bool currentKeys[256];

MouseState currMouse{};
std::vector<Listener*> InputHandler::listeners;

int gameW, gameH, displayW, displayH;

bool InputHandler::isMouseWithin(Rect rect) {
	if ((rect.x < mXPos) && (mXPos < rect.x + rect.w) && (rect.y < mYPos) && (mYPos < rect.y + rect.h))
		return true;
	return false;
}

void InputHandler::setup(int _gw, int _gh, int _ww, int _wh) {
	gameW = _gw;
	gameH = _gh;
	displayW = _ww;
	displayH = _wh;
}


void InputHandler::onKeyDown(unsigned char key, int x, int y) {
	currentKeys[key] = true;
	for (auto l : listeners)
		l->onKeyDown(key);
}
void InputHandler::onKeyUp(unsigned char key, int x, int y) {
	currentKeys[key] = false;
	for (auto l : listeners)
		l->onKeyUp(key);
}

int a;
void InputHandler::mouseEvent(int button, int state, int x, int y) {
	currMouse = { button, state, x, y };
	if (button == GLUT_LEFT_BUTTON)
		currMouse.leftDown = (state == GLUT_DOWN);
	if (button == GLUT_RIGHT_BUTTON)
		currMouse.rightDown = (state == GLUT_DOWN);

	motionMouseEvent(x, y);

	//for (auto l : listeners)
	//	l->onMouseEvent();

	//printf("%f, %f\n", mXPos, mYPos);
}

void InputHandler::motionMouseEvent(int x, int y) {
	//transform the mouse to use the same coordinates as the game objects themselves (-1, 1 instead of 0-800 or however many pixels wide)
	//mXPos = ((float(x) / gameW) * 2) - 1;
	//mYPos = (((float(y) / gameH) * 2) - 1) * -1;

	mdx = mXPos - x;
	mdy = mYPos - y;

	for (auto l : listeners)
		l->onMouseEvent(mdx, mdy);

	mXPos = x;
	mYPos = y;

}

bool InputHandler::isKeyDown(unsigned char key) {
	return currentKeys[key] || currentKeys[toupper(key)];
}

bool InputHandler::isKeyUp(unsigned char key) {
	return !isKeyDown(key);
}

bool InputHandler::isButtonDown(int button) {
	if (button == GLUT_LEFT_BUTTON)
		return currMouse.leftDown;
	return currMouse.rightDown;
}

bool InputHandler::isButtonUp(int button) {
	if (button == GLUT_LEFT_BUTTON)
		return !currMouse.leftDown;
	return!currMouse.rightDown;
}
