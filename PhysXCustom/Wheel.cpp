#include "Wheel.h"

Wheel::Wheel(const physx::PxTransform& pose) : DynamicObject(pose)
{
	SetMaterial("wheel");
	CreateShape(physx::PxCapsuleGeometry(0.5f, 0.2f), { 0, 0, 0 });
	SetDensity(5.0f);
	InitShapes();
}

void Wheel::Render()
{
	RenderShapes();
}