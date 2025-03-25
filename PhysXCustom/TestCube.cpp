#include "TestCube.h"
#include <GL/freeglut_std.h>

TestCube::TestCube() : PxDynamicObject(physx::PxTransform(physx::PxIdentity))
{
	SetMaterial("testMat");
	CreateShape(physx::PxSphereGeometry());
	SetDensity(1);
	InitShapes();
}

void TestCube::Render()
{
	glPushMatrix();

	glColor3f(1.0f, 0.0f, 0.0f);
	glMultMatrixf(GetGLMatrix(GetPose(shapes[0])));
	glutSolidSphere(shapes[0]->getGeometry().sphere().radius, 5, 5);

	glPopMatrix();
}
