#pragma once

#include "PxPhysicsAPI.h"

struct UserData
{
	physx::PxVec3 colour;

	UserData(physx::PxVec3 _colour)
	{
		colour = _colour;
	}
};