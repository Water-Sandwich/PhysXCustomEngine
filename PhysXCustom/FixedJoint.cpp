#include "FixedJoint.h"
#include "PhysicsEngine.h"

FixedJoint::FixedJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2)
{
	joint = PhysicsEngine::createFixedJoint(actor1, frame1, actor2, frame2);
}