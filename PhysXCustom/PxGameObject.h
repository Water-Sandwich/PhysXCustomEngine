#pragma once
#include "GameObject.h"
#include "PxPhysicsAPI.h"

class PxGameObject : public GameObject
{
public:
	physx::PxActor* actor;

	PxGameObject();
	~PxGameObject();

	physx::PxMaterial* material;

	virtual physx::PxShape* CreateShape(const physx::PxGeometry& geom) = 0;
};