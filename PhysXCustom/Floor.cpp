#include "Floor.h"
#include "GL/freeglut.h"

using namespace physx;

Floor::Floor() : PxStaticObject(PxTransformFromPlaneEquation(PxPlane({0,1,0}, 0)))
{
	SetMaterial("testMat");
	CreateShape(PxPlaneGeometry(), { .5, .5, .5 });
	InitShapes();
}

void Floor::Render()
{
	glPushMatrix();

	RenderShapes();

	glPopMatrix();
}