#include "SteelBeam.h"

SteelBeam::SteelBeam(const physx::PxTransform& pose) : DynamicObject(pose)
{
	SetMaterial("steel");
	CreateShape(physx::PxBoxGeometry(.2f, 1.25f, 0.2f), { .25f, .25f, .25f });
	SetDensity(7500.f);
	InitShapes();

	SetFilters(Layer::House, Layer::House);
}

void SteelBeam::Render()
{
	RenderShapes();
}