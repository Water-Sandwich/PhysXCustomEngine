#include "SphericalJoint.h"
#include "PhysicsEngine.h"

SphericalJoint::SphericalJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2) : Joint(actor1, actor2)
{
	joint = PhysicsEngine::createSphericalJoint(actor1, frame1, actor2, frame2);
}

void SphericalJoint::SetHardLimitCone(physx::PxReal yLimit, physx::PxReal zLimit, physx::PxReal contactDist)
{
	physx::PxJointLimitCone limit(yLimit, zLimit, contactDist);
	((physx::PxSphericalJoint*)joint)->setLimitCone(limit);
}

void SphericalJoint::SetSoftLimitCone(physx::PxReal yLimit, physx::PxReal zLimit, physx::PxReal stiffness, physx::PxReal damping)
{
	physx::PxSpring spring(stiffness, damping);
	physx::PxJointLimitCone limit(yLimit, zLimit, spring);
	((physx::PxSphericalJoint*)joint)->setLimitCone(limit);
}