#include "HouseBrick.h"

using namespace physx;

HouseBrick::HouseBrick(const physx::PxTransform& pose, const physx::PxVec3& scale, const physx::PxVec3& color) : DynamicObject(pose) {
	SetMaterial("brick");
	CreateShape(PxBoxGeometry(scale), color);
	SetDensity(1);
	InitShapes();
}

void HouseBrick::Render()
{
	RenderShapes();
}
