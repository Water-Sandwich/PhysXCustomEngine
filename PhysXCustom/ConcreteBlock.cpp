#include "ConcreteBlock.h"

ConcreteBlock::ConcreteBlock(const physx::PxTransform& pose) : DynamicObject(pose)
{
	SetMaterial("concrete");
	CreateShape(physx::PxBoxGeometry(0.5f, .25f, .25f), { .1f, .1f, .1f });
	SetDensity(2400.f);
	InitShapes();

	SetFilters(Layer::House, Layer::House);
}

void ConcreteBlock::Render()
{
	RenderShapes();
}