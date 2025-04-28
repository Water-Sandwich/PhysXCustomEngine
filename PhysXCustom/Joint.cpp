#include "Joint.h"

Joint::Joint(physx::PxRigidActor* actor1, physx::PxRigidActor* actor2)
{
	start = actor1;
	end = actor2;
}