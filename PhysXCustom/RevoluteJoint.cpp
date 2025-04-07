#include "RevoluteJoint.h"
#include "PhysicsEngine.h"

RevoluteJoint::RevoluteJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2)
{
	joint = PhysicsEngine::createRevoluteJoint(actor1, frame1, actor2, frame2);
}