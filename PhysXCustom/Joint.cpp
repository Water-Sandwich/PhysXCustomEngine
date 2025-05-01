#include "Joint.h"

Joint::Joint(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2)
{
	start = actor1;
	end = actor2;
}

Joint::Joint(PxGameObject* actor1, PxGameObject* actor2)
{
	start = (physx::PxRigidActor*)actor1->actor;
	end = (physx::PxRigidActor*)actor2->actor;
}

void Joint::SetBreakable(physx::PxReal force, physx::PxReal torque)
{
	joint->setBreakForce(force, torque);
}