#include "HouseFloor.h"

using namespace physx;

HouseFloor::HouseFloor(const physx::PxTransform& pose, const physx::PxVec3& scale, const physx::PxVec3& color) : DynamicObject(pose){
	SetMaterial("concrete");
	CreateShape(physx::PxBoxGeometry(scale), color);
	SetDensity(1);
	InitShapes();
}

void HouseFloor::Update(float dt)
{
	auto s = ((PxRigidDynamic*)actor)->getGlobalPose();
	if (s.p.y < 6) {
		printf("YOU WIN!\n");
	}
}
