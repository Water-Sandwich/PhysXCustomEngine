#include "GlassFragment.h"

GlassFragment::GlassFragment(const physx::PxTransform& pose) : DynamicObject(pose)
{
	SetMaterial("glass");
	CreateShape(physx::PxBoxGeometry(0.1f, 0.1f, 0.005f), { 0, 0, .5f });
	SetDensity(2.5f); // .5f
	InitShapes();
}

void GlassFragment::Render()
{
	RenderShapes();
}