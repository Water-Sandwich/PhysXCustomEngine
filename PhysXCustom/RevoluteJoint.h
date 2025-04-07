#pragma once
#include "Joint.h"
class RevoluteJoint : public Joint
{
public:
	RevoluteJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2);
};