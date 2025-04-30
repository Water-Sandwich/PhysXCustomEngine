#pragma once
#include "Joint.h"

class FixedJoint : public Joint
{
public:
	FixedJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2);
};