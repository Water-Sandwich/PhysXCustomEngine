#pragma once

#include "DynamicObject.h"

class CannonBall : public DynamicObject
{
public:
	CannonBall(const physx::PxTransform& pose);

	void Update(float dt) override;
	void Render() override;

private:
	float timer = 0.0f;
	float duration = 2500.0f;
};