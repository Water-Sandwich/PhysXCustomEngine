#pragma once
#include "GameObject.h"
#include "PxPhysicsAPI.h"
#include <string>

class PxGameObject : public GameObject
{
public:
	physx::PxActor* actor;
	physx::PxMaterial* material;

	PxGameObject();
	~PxGameObject();

	virtual physx::PxShape* CreateShape(const physx::PxGeometry& geom) = 0;
	physx::PxMaterial* SetMaterial(std::string name);
};