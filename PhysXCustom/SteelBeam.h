#pragma once
#include "DynamicObject.h"
class SteelBeam : public DynamicObject
{
private:
	physx::PxVec3 bottom;
	physx::PxVec3 pos;

public:
	SteelBeam(const physx::PxVec3& beamSize, const physx::PxTransform& pose, const physx::PxVec3& color);
	physx::PxTransform getBottom() const;
	physx::PxTransform getPos() const;
};

