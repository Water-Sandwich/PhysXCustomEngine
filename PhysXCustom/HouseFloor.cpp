#include "HouseFloor.h"

using namespace physx;

HouseFloor::HouseFloor(const physx::PxTransform& pose, const physx::PxVec3& scale, const physx::PxVec3& color) : DynamicObject(pose){
	SetMaterial("wood");
	CreateShape(physx::PxBoxGeometry(scale), color);

	auto s = CreateShape(physx::PxBoxGeometry(3,5,3), color);
	s->setLocalPose(PxTransform({ 0,5,0 }));

	s = CreateShape(physx::PxBoxGeometry(scale.x * 0.8f, 1, scale.z * 0.8f), color);
	s->setLocalPose(PxTransform({ 0,5,0 }));

	SetDensity(0.420);
	InitShapes();
}

void HouseFloor::Update(float dt)
{
	auto s = ((PxRigidDynamic*)actor)->getGlobalPose();
	if (s.p.y < 6) {
		printf("YOU WIN!\n");
	}
}
