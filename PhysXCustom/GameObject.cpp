#include "GameObject.h"
#include "Game.h"

void GameObject::DeleteThis() {
	Game::DeleteObject(this);
}

GameObject::~GameObject() {
	//LOG("GameObject deleted");
}