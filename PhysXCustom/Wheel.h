#pragma once

#include "DynamicObject.h"

class Wheel : public DynamicObject
{
public:
	Wheel(const physx::PxTransform& pose);

	void Update(float dt) override {};
	void Render() override;
};