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

	void Update(float dt) override {};

	void SetBreakable(physx::PxReal force, physx::PxReal torque);
};