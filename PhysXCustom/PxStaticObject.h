#pragma once
#include "PxGameObject.h"
class PxStaticObject : public PxGameObject
{
public:
	virtual physx::PxShape* CreateShape(const physx::PxGeometry& geom) override;
};