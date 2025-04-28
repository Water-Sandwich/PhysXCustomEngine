#pragma once
#include "Joint.h"
class DistanceJoint : public Joint
{
public:
	DistanceJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2);

	void SetStiffness(physx::PxReal val);
	physx::PxReal GetStiffness();

	void SetDamping(physx::PxReal val);
	physx::PxReal GetDamping();
};