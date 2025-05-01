#include "FixedJoint.h"
#include "PhysicsEngine.h"

FixedJoint::FixedJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2) : Joint(actor1, actor2)
{
	joint = PhysicsEngine::createFixedJoint(actor1, frame1, actor2, frame2);
}

FixedJoint::FixedJoint(PxGameObject* actor1, const physx::PxTransform& frame1, PxGameObject* actor2, const physx::PxTransform& frame2) : Joint(actor1, actor2)
{
	joint = PhysicsEngine::createFixedJoint((physx::PxRigidActor*)actor1->actor, frame1, (physx::PxRigidActor*)actor2->actor, frame2);
}
