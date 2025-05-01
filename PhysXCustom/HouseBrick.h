#pragma once
#include "DynamicObject.h"
#include <PxPhysicsAPI.h>

class HouseBrick : public DynamicObject
{
public:
	HouseBrick(const physx::PxTransform& pose, const physx::PxVec3& scale, const physx::PxVec3& color);
	void Render() override;
};

