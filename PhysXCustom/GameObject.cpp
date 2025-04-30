#include "GameObject.h"
#include "Game.h"

void GameObject::DeleteThis() {
	Game::DeleteObject(this);
}

void GameObject::AddThis(){
	Game::AddObject(this);
}

GameObject::~GameObject() {
	//LOG("GameObject deleted");
}