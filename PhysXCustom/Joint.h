#pragma once

#include "PxPhysicsAPI.h"
#include "GameObject.h"

class Joint : public GameObject
{
public:
	physx::PxJoint* joint = nullptr;
	physx::PxRigidActor* start;
	physx::PxRigidActor* end;

	Joint(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2);
};