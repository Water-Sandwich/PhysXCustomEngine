#pragma once
#include "GameObject.h"
#include "PxPhysicsAPI.h"

class PxGameObject : public GameObject
{
public:
	physx::PxActor* actor;

	PxGameObject();
	~PxGameObject();
};

