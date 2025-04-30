#pragma once

#include "DynamicObject.h"

class ConcreteBlock : public DynamicObject
{
public:
	ConcreteBlock(const physx::PxTransform& pose);

	void Update(float dt) override {};
	void Render() override;
};