#include "GlassPanel.h"

GlassPanel::GlassPanel(const physx::PxTransform& pose) : DynamicObject(pose)
{
	SetMaterial("glass");
	CreateShape(physx::PxBoxGeometry(.53f, 0.005f, .53f), { 0, 0, .5f });
	SetDensity(2500.f);
	InitShapes();

	SetFilters(Layer::House, Layer::House);
}

void GlassPanel::Render()
{
	RenderShapes();
}