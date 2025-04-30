#include "SteelBeam.h"

SteelBeam::SteelBeam(const physx::PxTransform& pose) : DynamicObject(pose)
{
	SetMaterial("steel");
	CreateShape(physx::PxBoxGeometry(2.5f, 0.15f, 0.2f), { .25f, .25f, .25f });
	SetDensity(7.5f); // 5000kg.
	InitShapes();
}

void SteelBeam::Render()
{
	RenderShapes();
}