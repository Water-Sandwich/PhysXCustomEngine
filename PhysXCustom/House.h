#pragma once

#include "GameObject.h"
#include "PxPhysicsAPI.h"
#include "HouseBrick.h"

class House : public GameObject
{
private:
	std::vector<HouseBrick*> bricks;
public:
	//x and y are the smaller row sizes
	House(int wallHeight, int bricksX, int bricksY, const physx::PxVec3& brickSize, const physx::PxTransform& pose, const physx::PxVec3& color, float gap = 0.1f);
	~House() = default;
};

