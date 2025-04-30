#pragma once

#include "DynamicObject.h"

class GlassFragment : public DynamicObject
{
public:
	GlassFragment(const physx::PxTransform& pose);

	void Update(float dt) override {};
	void Render() override;
};