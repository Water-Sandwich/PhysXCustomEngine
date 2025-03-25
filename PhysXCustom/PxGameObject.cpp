#include "PxGameObject.h"
#include "PhysicsEngine.h"

PxGameObject::PxGameObject()
{
	actor = nullptr;
	material = nullptr;
}

PxGameObject::~PxGameObject()
{
	if(actor)
		PhysicsEngine::RemoveActor(actor);
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