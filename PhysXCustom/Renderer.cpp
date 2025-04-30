#include "Renderer.h"
#include "UserData.h"
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
	PxVec3 colour = ((UserData*)shape->userData)->colour;
	glColor3f(colour.x, colour.y, colour.z);
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
		RenderBox(geometry);
		break;
	case PxGeometryType::eCONVEXMESH:
		RenderConvexMesh(geometry);
		break;
	case PxGeometryType::eTRIANGLEMESH:
		RenderTriangleMesh(geometry);
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

void Renderer::RenderBox(const physx::PxGeometryHolder& geometry)
{
	PxVec3 halfSize = geometry.box().halfExtents;
	glScalef(halfSize.x, halfSize.y, halfSize.y);
	glutSolidCube(2.f);
}

void Renderer::RenderConvexMesh(const physx::PxGeometryHolder& geometry)
{
	PxConvexMesh* mesh = geometry.convexMesh().convexMesh;
	PxU32 numPolys = mesh->getNbPolygons();
	const PxVec3* verts = mesh->getVertices();
	const PxU8* indices = mesh->getIndexBuffer();

	for (PxU32 i = 0; i < numPolys; i++)
	{
		PxHullPolygon face;
		if (mesh->getPolygonData(i, face))
		{
			glBegin(GL_POLYGON);
			glNormal3f(face.mPlane[0], face.mPlane[1], face.mPlane[2]);
			const PxU8* faceIdx = indices + face.mIndexBase;
			for (PxU32 j = 0; j < face.mNbVerts; j++)
			{
				PxVec3 v = verts[faceIdx[j]];
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
		}
	}
}

void Renderer::RenderTriangleMesh(const physx::PxGeometryHolder& geometry)
{
	PxTriangleMesh* mesh = geometry.triangleMesh().triangleMesh;
	const PxVec3* verts = mesh->getVertices();
	PxU16* trigs = (PxU16*)mesh->getTriangles();
	const PxU32 numTrigs = mesh->getNbTriangles();

	for (PxU32 i = 0; i < numTrigs * 3; i += 3)
	{
		PxVec3 v0 = verts[trigs[i]];
		PxVec3 v1 = verts[trigs[i + 1]];
		PxVec3 v2 = verts[trigs[i + 2]];
		PxVec3 n = (v1 - v0).cross(v2 - v0);
		n.normalize();

		glBegin(GL_POLYGON);
		glNormal3f(n.x, n.y, n.z);
		glVertex3f(v0.x, v0.y, v0.z);
		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glEnd();
	}
}

void Renderer::RenderCloth(const Cloth& cloth)
{
	const PxClothMeshDesc* mesh_desc = cloth.getMesh();
	PxVec3* color = cloth.getColor();

	PxU32 quad_count = mesh_desc->quads.count;
	PxU32* quads = (PxU32*)mesh_desc->quads.data;

	auto* clothActor = ((PxCloth*)cloth.actor);

	std::vector<PxVec3> verts(clothActor->getNbParticles());
	std::vector<PxVec3> norms(verts.size(), PxVec3(0.f, 0.f, 0.f));

	//get verts data
	clothActor->lockParticleData();

	PxClothParticleData* particle_data = clothActor->lockParticleData();
	if (!particle_data)
		return;
	// copy vertex positions
	for (PxU32 j = 0; j < verts.size(); j++)
		verts[j] = particle_data->particles[j].pos;

	particle_data->unlock();

	for (PxU32 i = 0; i < quad_count * 4; i += 4)
	{
		PxVec3 v0 = verts[quads[i]];
		PxVec3 v1 = verts[quads[i + 1]];
		PxVec3 v2 = verts[quads[i + 2]];
		PxVec3 n = -((v1 - v0).cross(v2 - v0));

		norms[quads[i]] += n;
		norms[quads[i + 1]] += n;
		norms[quads[i + 2]] += n;
		norms[quads[i + 3]] += n;
	}

	for (PxU32 i = 0; i < norms.size(); i++)
		norms[i].normalize();

	PxTransform pose = clothActor->getGlobalPose();
	PxMat44 shapePose(pose);

	glColor4f(color->x, color->y, color->z, 1.f);

	glPushMatrix();
	glMultMatrixf((float*)&shapePose);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(PxVec3), &verts.front());
	glNormalPointer(GL_FLOAT, sizeof(PxVec3), &norms.front());

	glDrawElements(GL_QUADS, quad_count * 4, GL_UNSIGNED_INT, quads);

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
}