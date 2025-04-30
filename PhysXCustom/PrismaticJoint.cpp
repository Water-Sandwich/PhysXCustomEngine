#include "PrismaticJoint.h"
#include "PhysicsEngine.h"

PrismaticJoint::PrismaticJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2) : Joint(actor1, actor2)
{
	joint = PhysicsEngine::createPrismaticJoint(actor1, frame1, actor2, frame2);
}

void PrismaticJoint::SetHardLimit(physx::PxReal min, physx::PxReal max, physx::PxReal contactDist)
{
	physx::PxJointLinearLimitPair limit(physx::PxTolerancesScale(), min, max, contactDist);
	((physx::PxPrismaticJoint*)joint)->setLimit(limit);
}

void PrismaticJoint::SetSoftLimit(physx::PxReal min, physx::PxReal max, physx::PxReal stiffness, physx::PxReal damping)
{
	physx::PxSpring spring(stiffness, damping);
	physx::PxJointLinearLimitPair limit(min, max, spring);
	((physx::PxPrismaticJoint*)joint)->setLimit(limit);
}