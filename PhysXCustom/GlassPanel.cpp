#include "GlassPanel.h"

GlassPanel::GlassPanel(const physx::PxTransform& pose) : DynamicObject(pose)
{
	SetMaterial("glass");
	CreateShape(physx::PxBoxGeometry(1.0f, 0.025f, 1.0f), { 0, 0, .5f });
	SetDensity(2500.f);
	InitShapes();

	SetFilters(Layer::House, Layer::House);
}

void GlassPanel::Render()
{
	RenderShapes();
}