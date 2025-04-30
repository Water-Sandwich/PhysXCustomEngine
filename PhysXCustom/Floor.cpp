#include "Floor.h"

using namespace physx;

Floor::Floor() : StaticObject(PxTransformFromPlaneEquation(PxPlane({0,1,0}, 0)))
{
	SetMaterial("testMat");
	CreateShape(PxPlaneGeometry(), { 1, 1, 1 });
	InitShapes();
}

void Floor::Render()
{
	RenderShapes();
}