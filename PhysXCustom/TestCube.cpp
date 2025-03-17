#include "TestCube.h"
#include <GL/freeglut_std.h>

void TestCube::Render()
{
	//glColor3b(255,255,255);

	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(2, 16, 16);

}
