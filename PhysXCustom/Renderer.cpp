#include "Renderer.h"
#include <GL/freeglut.h>

using namespace physx;

static const float planeData[] = {
	-1.f, 0.f, -1.f, 0.f, 1.f, 0.f, -1.f, 0.f, 1.f, 0.f, 1.f, 0.f,
	1.f, 0.f, 1.f, 0.f, 1.f, 0.f, -1.f, 0.f, -1.f, 0.f, 1.f, 0.f,
	1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, -1.f, 0.f, 1.f, 0.f
};

void Renderer::Setup(int x, int y, const char* title)
{
	//more GLUT init
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(x, y);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(title);

	// Setup lighting
	glEnable(GL_LIGHTING);
	PxReal ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.f };
	PxReal diffuseColor[] = { 0.7f, 0.7f, 0.7f, 1.f };
	PxReal position[] = { 50.f, 50.f, 100.f, 0.f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
}

void Renderer::Start()
{
	glClearColor(0, 0.1, 0.1, 1); //backround color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Setup camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.f, (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 1.f, 10000.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Renderer::RenderGeometry(const physx::PxGeometryHolder& geometry)
{
	switch (geometry.getType())
	{
	case PxGeometryType::eSPHERE:
		RenderSphere(geometry);
		break;
	case PxGeometryType::ePLANE:
		RenderPlane();
		break;
	case PxGeometryType::eCAPSULE:
		break;
	case PxGeometryType::eBOX:
		break;
	case PxGeometryType::eCONVEXMESH:
		break;
	case PxGeometryType::eTRIANGLEMESH:
		break;
	case PxGeometryType::eHEIGHTFIELD:
		break;
	}
}

void Renderer::RenderSphere(const physx::PxGeometryHolder& geometry)
{
	glutSolidSphere(geometry.sphere().radius, 16, 16);
}

void Renderer::RenderPlane()
{
	glScalef(10240, 0, 10240);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 2 * 3 * sizeof(float), planeData);
	glNormalPointer(GL_FLOAT, 2 * 3 * sizeof(float), planeData + 3);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
