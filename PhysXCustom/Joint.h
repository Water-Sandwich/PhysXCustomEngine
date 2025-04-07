#pragma once

#include "PxPhysicsAPI.h"
#include "GameObject.h"

class Joint : public GameObject
{
public:
	physx::PxJoint* joint = nullptr;

	Joint();
};