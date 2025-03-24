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

physx::PxMaterial* PxGameObject::SetMaterial(std::string name)
{
	return PhysicsEngine::GetMaterial(name);
}
