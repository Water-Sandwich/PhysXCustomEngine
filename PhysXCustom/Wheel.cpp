#include "Wheel.h"

Wheel::Wheel(const physx::PxTransform& pose) : DynamicObject(pose)
{
	SetMaterial("wheel");
	CreateShape(physx::PxCapsuleGeometry(0.35f, 0.2f), { 0, 0, 0 });
	SetDensity(2500.f);
	InitShapes();
}

void Wheel::Render()
{
	RenderShapes();
}