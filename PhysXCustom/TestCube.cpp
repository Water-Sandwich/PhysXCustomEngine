#include "TestCube.h"
#include "Renderer.h"
#include <GL/freeglut_std.h>

TestCube::TestCube(const physx::PxTransform& pose) : PxDynamicObject(pose)
{
	SetMaterial("testMat");
	CreateShape(physx::PxSphereGeometry(5.f), { 0, 0, 1 });
	CreateShape(physx::PxCapsuleGeometry(2.f, 10.f), { 0, 0, 1 });
	SetDensity(1);
	InitShapes();
}

void TestCube::Render()
{
	glPushMatrix();

	RenderShapes();

	glPopMatrix();
}