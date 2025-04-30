#pragma once

#include "DynamicObject.h"

class SteelBeam : public DynamicObject
{
public:
	SteelBeam(const physx::PxTransform& pose);

	void Update(float dt) override {};
	void Render() override;
};