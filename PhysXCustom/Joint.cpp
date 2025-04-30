#include "Joint.h"

Joint::Joint(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2)
{
	start = actor1;
	end = actor2;


}

void Joint::SetBreakable(physx::PxReal force, physx::PxReal torque)
{
	joint->setBreakForce(force, torque);
}
