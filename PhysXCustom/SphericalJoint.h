#pragma once
#include "Joint.h"
class SphericalJoint : public Joint
{
public:
	SphericalJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2);

	void SetHardLimitCone(physx::PxReal yLimit, physx::PxReal zLimit, physx::PxReal contactDist);
	void SetSoftLimitCone(physx::PxReal yLimit, physx::PxReal zLimit, physx::PxReal stiffness, physx::PxReal damping);
};