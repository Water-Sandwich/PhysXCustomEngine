#include "PxGameObject.h"
#include "Game.h"

PxGameObject::PxGameObject()
{
	PhysicsEngine::AddActor(actor);
}

PxGameObject::~PxGameObject()
{
	PhysicsEngine::RemoveActor(actor);
}