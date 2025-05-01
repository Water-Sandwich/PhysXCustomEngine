#include "CannonBall.h"

CannonBall::CannonBall(const physx::PxTransform& pose) : DynamicObject(pose)
{
	SetMaterial("steel");
	CreateShape(physx::PxSphereGeometry(1.0f), { 0.2f, 0.2f, 0.2f });
	SetDensity(7.5f);
	InitShapes();
}

void CannonBall::Update(float dt)
{
	DynamicObject::Update(dt);

	timer += dt;
	if (timer > duration) { DeleteThis(); }
}

void CannonBall::Render()
{
	RenderShapes();
}