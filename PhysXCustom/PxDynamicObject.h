#pragma once
#include "PxGameObject.h"
class PxDynamicObject : public PxGameObject
{
public:
	virtual physx::PxShape* CreateShape(const physx::PxGeometry& geom) override;
	void SetDensity(physx::PxReal density);
};