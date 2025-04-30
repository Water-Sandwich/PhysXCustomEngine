#include "ConcreteBlock.h"

ConcreteBlock::ConcreteBlock(const physx::PxTransform& pose) : DynamicObject(pose)
{
	SetMaterial("concrete");
	CreateShape(physx::PxBoxGeometry(0.5f, .25f, .25f), { .75f, .5f, .5f });
	SetDensity(2.5f); // 600f.
	InitShapes();
}

void ConcreteBlock::Render()
{
	RenderShapes();
}