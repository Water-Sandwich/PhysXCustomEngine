#include "PxGameObject.h"
#include "Game.h"

PxGameObject::PxGameObject()
{
	Game::instance->AddActor(actor);
}

PxGameObject::~PxGameObject()
{
	Game::instance->RemoveActor(actor);
}
