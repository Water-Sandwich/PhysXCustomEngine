#pragma once
#include "PxGameObject.h"
class PxDynamicObject : public PxGameObject
{
public:
	PxDynamicObject(const physx::PxTransform& pose);
	virtual physx::PxShape* CreateShape(const physx::PxGeometry& geometry, const physx::PxVec3& colour) override;
	void SetDensity(physx::PxReal density);
};