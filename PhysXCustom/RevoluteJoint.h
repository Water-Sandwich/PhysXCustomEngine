#pragma once
#include "Joint.h"
class RevoluteJoint : public Joint
{
public:
	RevoluteJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2);

	void SetDriveVelocity(physx::PxReal val);
	physx::PxReal GetDriveVelocity();
	
	void SetLimits(physx::PxReal lower, physx::PxReal upper);
};