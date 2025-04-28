#include "DistanceJoint.h"
#include "PhysicsEngine.h"

DistanceJoint::DistanceJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2) : Joint(actor1, actor2)
{
	joint = PhysicsEngine::createDistanceJoint(actor1, frame1, actor2, frame2);
}

void DistanceJoint::SetStiffness(physx::PxReal val)
{
	((physx::PxDistanceJoint*)joint)->setStiffness(val);
}

physx::PxReal DistanceJoint::GetStiffness()
{
	return ((physx::PxDistanceJoint*)joint)->getStiffness();
}

void DistanceJoint::SetDamping(physx::PxReal val)
{
	((physx::PxDistanceJoint*)joint)->setDamping(val);
}

physx::PxReal DistanceJoint::GetDamping()
{
	return ((physx::PxDistanceJoint*)joint)->getDamping();
}