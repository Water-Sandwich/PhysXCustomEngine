#include "Floor.h"
#include "GL/freeglut.h"

using namespace physx;

Floor::Floor() : PxStaticObject(PxTransformFromPlaneEquation(PxPlane({1,0,0}, 0)))
{
	SetMaterial("testMat");
	CreateShape(PxPlaneGeometry());
	InitShapes();
}

void Floor::Render()
{
	glPushMatrix();

	glColor3f(1.0f, 0.0f, 0.0f);
	RenderShapes();

	glPopMatrix();
}
