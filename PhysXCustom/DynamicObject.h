#pragma once
#include "PxGameObject.h"

class DynamicObject : public PxGameObject
{
public:
	DynamicObject(const physx::PxTransform& pose);
	virtual physx::PxShape* CreateShape(const physx::PxGeometry& geometry, const physx::PxVec3& colour) override;
	void SetDensity(physx::PxReal density);
};