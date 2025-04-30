#pragma once

class Listener {
public:
	void virtual onKeyDown(unsigned char c) {}
	void virtual onKeyUp(unsigned char c) {}
	void virtual onMouseEvent(int x, int y) {}

	Listener();
	~Listener();
};