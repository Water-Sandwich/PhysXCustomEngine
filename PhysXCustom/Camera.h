#pragma once
#include "GameObject.h"
#include "InputHandler.h"
#include "PxActor.h"
#include <foundation/PxVec3.h>

class Camera : public GameObject, public Listener
{
public:
	physx::PxVec3 pos, dir;
	float speed = 0.05;
	float sensitivity = 0.2;
	Camera();
	void Update(float dt) override;

	void onKeyDown(unsigned char c) override;
	void onKeyUp(unsigned char c) override;
	void onMouseEvent(int x, int y) override;
};

