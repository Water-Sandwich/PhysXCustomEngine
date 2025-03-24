#pragma once
#include "PxGameObject.h"
class PxStaticObject : public PxGameObject
{
public:
	PxStaticObject(const physx::PxTransform& pose);
	virtual physx::PxShape* CreateShape(const physx::PxGeometry& geometry) override;
};