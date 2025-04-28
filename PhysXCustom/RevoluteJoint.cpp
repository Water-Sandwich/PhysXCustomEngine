#include "RevoluteJoint.h"
#include "PhysicsEngine.h"

RevoluteJoint::RevoluteJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2) : Joint(actor1, actor2)
{
	joint = PhysicsEngine::createRevoluteJoint(actor1, frame1, actor2, frame2);
}

void RevoluteJoint::SetDriveVelocity(physx::PxReal val)
{
	physx::PxRigidDynamic* actor1 = (physx::PxRigidDynamic*)start;
	physx::PxRigidDynamic* actor2 = (physx::PxRigidDynamic*)end;
	if (actor1) actor1->wakeUp();
	if (actor2) actor2->wakeUp();
	((physx::PxRevoluteJoint*)joint)->setDriveVelocity(val);
	((physx::PxRevoluteJoint*)joint)->setRevoluteJointFlag(physx::PxRevoluteJointFlag::eDRIVE_ENABLED, true);
}

physx::PxReal RevoluteJoint::GetDriveVelocity()
{
	return ((physx::PxRevoluteJoint*)joint)->getDriveVelocity();
}

void RevoluteJoint::SetLimits(physx::PxReal lower, physx::PxReal upper)
{
	((physx::PxRevoluteJoint*)joint)->setLimit(physx::PxJointAngularLimitPair(lower, upper));
	((physx::PxRevoluteJoint*)joint)->setRevoluteJointFlag(physx::PxRevoluteJointFlag::eLIMIT_ENABLED, true);
}