#pragma once

#include "DynamicObject.h"

class GlassPanel : public DynamicObject
{
public:
	GlassPanel(const physx::PxTransform& pose);

	void Update(float dt) override {};
	void Render() override;
};