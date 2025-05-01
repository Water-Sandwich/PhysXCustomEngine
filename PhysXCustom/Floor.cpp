#include "Floor.h"

using namespace physx;

Floor::Floor() : StaticObject(PxTransformFromPlaneEquation(PxPlane({0,1,0}, 0)))
{
	SetMaterial("concrete");
	CreateShape(PxPlaneGeometry(), { .5, .5, .5 });
	InitShapes();
}

void Floor::Render()
{
	RenderShapes();
}