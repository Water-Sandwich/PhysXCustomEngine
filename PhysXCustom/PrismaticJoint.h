#pragma once
#include "Joint.h"
class PrismaticJoint : public Joint
{
public:
	PrismaticJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2);
	PrismaticJoint(PxGameObject* actor1, const physx::PxTransform& frame1, PxGameObject* actor2, const physx::PxTransform& frame2);

	void SetHardLimit(physx::PxReal min, physx::PxReal max, physx::PxReal contactDist);
	void SetSoftLimit(physx::PxReal min, physx::PxReal max, physx::PxReal stiffness, physx::PxReal damping);
};