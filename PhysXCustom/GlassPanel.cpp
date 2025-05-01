#include "GlassPanel.h"

GlassPanel::GlassPanel(const physx::PxTransform& pose) : DynamicObject(pose)
{
	SetMaterial("glass");
	CreateShape(physx::PxBoxGeometry(1.0f, 0.025f, 1.0f), { 0, 0, .5f });
	SetDensity(2.5f); // .5f
	InitShapes();
}

void GlassPanel::Render()
{
	RenderShapes();
}