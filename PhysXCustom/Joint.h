#pragma once

#include "PxPhysicsAPI.h"

class Joint
{
public:
	physx::PxJoint* joint = nullptr;

	Joint();
};