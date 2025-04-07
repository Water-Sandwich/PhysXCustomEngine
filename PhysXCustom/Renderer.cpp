#include "Renderer.h"
#include <GL/freeglut.h>

using namespace physx;

static const float planeData[] = {
	-1.f, 0.f, -1.f, 0.f, 1.f, 0.f, -1.f, 0.f, 1.f, 0.f, 1.f, 0.f,
	1.f, 0.f, 1.f, 0.f, 1.f, 0.f, -1.f, 0.f, -1.f, 0.f, 1.f, 0.f,
	1.f, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f, 0.f, -1.f, 0.f, 1.f, 0.f
};

static const float samples = 16;

void Renderer::Setup(int x, int y, const char* title)
{
	//more GLUT init
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(x, y);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(title);

	// Setup lighting
	PxReal specular_material[] = { .1f, .1f, .1f, 1.f };
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material);
	
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

void Renderer::RenderGeometry(PxShape* const shape)
{
	const PxGeometryHolder geometry = shape->getGeometry();
	switch (geometry.getType())
	{
	case PxGeometryType::eSPHERE:
		RenderSphere(geometry);
		break;
	case PxGeometryType::ePLANE:
		RenderPlane(shape);
		break;
	case PxGeometryType::eCAPSULE:
		RenderCapsule(geometry);
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
	glutSolidSphere(geometry.sphere().radius, samples, samples);
}

void Renderer::RenderPlane(PxShape* const plane)
{
	//rotate the plane so it renders correctly (why dont we just change planeData?)
	PxTransform pose = PxShapeExt::getGlobalPose(*plane, *plane->getActor());
	pose.q *= PxQuat(PxHalfPi, PxVec3(0.f, 1.f, 0.f));
	pose.p += PxVec3(0, -0.01, 0);
	PxMat44 planePose(pose);

	glPushMatrix();
	glMultMatrixf((float*)&planePose);
	glColor3f(1, 1, 1);

	glScalef(4096, 0, 4096);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 2 * 3 * sizeof(float), planeData);
	glNormalPointer(GL_FLOAT, 2 * 3 * sizeof(float), planeData + 3);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glPopMatrix();
}

void Renderer::RenderCapsule(const physx::PxGeometryHolder& geometry)
{
	const PxF32 radius = geometry.capsule().radius;
	const PxF32 halfHeight = geometry.capsule().halfHeight;

	//Sphere
	glPushMatrix();
	glTranslatef(halfHeight, 0.f, 0.f);
	glutSolidSphere(radius, samples, samples);
	glPopMatrix();

	//Sphere
	glPushMatrix();
	glTranslatef(-halfHeight, 0.f, 0.f);
	glutSolidSphere(radius, samples, samples);
	glPopMatrix();

	//Cylinder
	glPushMatrix();
	glTranslatef(-halfHeight, 0.f, 0.f);
	glRotatef(90.f, 0.f, 1.f, 0.f);

	GLUquadric* qobj = gluNewQuadric();
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluCylinder(qobj, radius, radius, halfHeight * 2.f, samples, samples);
	gluDeleteQuadric(qobj);
	glPopMatrix();
}
