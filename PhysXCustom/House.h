#pragma once

#include "PxPhysicsAPI.h"
#include "HouseBrick.h"
#include "SteelBeam.h"

class House : public GameObject
{
private:
	void MakeBricks(int wallHeight, int bricksX, int bricksY, const physx::PxVec3& brickSize, const physx::PxTransform& pose, const physx::PxVec3& color, float gap = 0.1f);
	void MakeBeams(const physx::PxVec3& beamSize, const physx::PxVec3 positions[4]);
public:
	std::vector<HouseBrick*> bricks;
	std::vector<SteelBeam*> beams;

	//x and y are the smaller row sizes
	House(int wallHeight, int bricksX, int bricksY, const physx::PxVec3& brickSize, const physx::PxTransform& pose, const physx::PxVec3& color, float gap = 0.1f);
	~House() = default;
};

