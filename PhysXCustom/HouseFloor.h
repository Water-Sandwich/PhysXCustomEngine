#pragma once
#include "DynamicObject.h"

class HouseFloor : public DynamicObject
{
public:
	HouseFloor(const physx::PxTransform& pose, const physx::PxVec3& scale, const physx::PxVec3& color);
	void Update(float dt) override;
};

