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
	((physx::PxRevoluteJoint*)joint)->setDriveForceLimit(1000.0f);
	((physx::PxRevoluteJoint*)joint)->setDriveGearRatio(1.0f);
	((physx::PxRevoluteJoint*)joint)->setRevoluteJointFlag(physx::PxRevoluteJointFlag::eDRIVE_ENABLED, true);
}

physx::PxReal RevoluteJoint::GetDriveVelocity()
{
	return ((physx::PxRevoluteJoint*)joint)->getDriveVelocity();
}

void RevoluteJoint::SetHardLimits(physx::PxReal lower, physx::PxReal upper, physx::PxReal contactDist)
{
	physx::PxJointAngularLimitPair limitPair(lower, upper, contactDist);
	((physx::PxRevoluteJoint*)joint)->setLimit(limitPair);
	((physx::PxRevoluteJoint*)joint)->setRevoluteJointFlag(physx::PxRevoluteJointFlag::eLIMIT_ENABLED, true);
}

void RevoluteJoint::SetSoftLimits(physx::PxReal lower, physx::PxReal upper, physx::PxReal stiffness, physx::PxReal damping)
{
	physx::PxSpring spring(stiffness, damping);
	physx::PxJointAngularLimitPair limitPair(lower, upper, spring);
	((physx::PxRevoluteJoint*)joint)->setLimit(limitPair);
	((physx::PxRevoluteJoint*)joint)->setRevoluteJointFlag(physx::PxRevoluteJointFlag::eLIMIT_ENABLED, true);
}