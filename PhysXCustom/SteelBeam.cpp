#include "SteelBeam.h"

using namespace physx;

SteelBeam::SteelBeam(const physx::PxVec3& beamSize, const physx::PxTransform& pose, const physx::PxVec3& color) : DynamicObject(pose)
{
	SetMaterial("testMat");
	CreateShape(PxBoxGeometry(beamSize), color);
	SetDensity(1);
	InitShapes();
	bottom = { 0, -bottom.y, 0 };
	pos = pose.p;
}

PxTransform SteelBeam::getBottom() const
{
	return PxTransform(bottom, PxQuat(PxHalfPi, {0,0,1}));
}

physx::PxTransform SteelBeam::getPos() const
{
	return physx::PxTransform(pos);
}
