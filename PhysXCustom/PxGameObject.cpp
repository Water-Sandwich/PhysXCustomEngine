#include "PxGameObject.h"
#include "PhysicsEngine.h"
#include "Renderer.h"
#include "GL/freeglut.h"

PxGameObject::PxGameObject()
{
	actor = nullptr;
	material = nullptr;
}

PxGameObject::~PxGameObject()
{
	for (auto shape : shapes)
		delete shape->userData;

	if(actor)
		PhysicsEngine::RemoveActor(actor);
}

void PxGameObject::RenderShapes()
{
	for (auto shape : shapes) {
		glPushMatrix();
		glMultMatrixf(GetGLMatrix(GetPose(shape)));
		Renderer::RenderGeometry(shape);
		glPopMatrix();
	}
}

void PxGameObject::SetTrigger(bool isTrigger)
{
	for (auto shape : shapes)
	{
		shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, !isTrigger);
		shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, isTrigger);
	}
}

void PxGameObject::SetFilters(Layer filterGroup, Layer filterMask)
{
	for (auto shape : shapes)
	{
		shape->setSimulationFilterData(physx::PxFilterData((int)filterGroup, (int)filterMask, 0, 0));
	}
}

void PxGameObject::SetMaterial(std::string name)
{
	material = PhysicsEngine::GetMaterial(name);
}

physx::PxRigidActor* PxGameObject::GetRigid()
{
	return static_cast<physx::PxRigidActor*>(actor);
}

void PxGameObject::InitShapes()
{
	auto rigid = GetRigid();
	shapes = std::vector<physx::PxShape*>(rigid->getNbShapes());
	rigid->getShapes(static_cast<physx::PxShape**>(&shapes.front()), shapes.size());
}

physx::PxTransform PxGameObject::GetPose(physx::PxShape* shape)
{
	return physx::PxShapeExt::getGlobalPose(*shape, *GetRigid());
}

physx::PxMat44 PxGameObject::GetMatrix(const physx::PxTransform& transform)
{
	return physx::PxMat44(transform);
}

float* PxGameObject::GetGLMatrix(const physx::PxTransform& transform)
{
	auto mat = GetMatrix(transform);
	return (float*)&mat;
}