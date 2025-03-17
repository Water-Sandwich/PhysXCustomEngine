//
// Created by d on 2/16/24.
//
#include "GameObject.h"
#include "Game.h"

void GameObject::DeleteThis() {
	Game::DeleteObject(this);
}

GameObject::~GameObject() {
	//LOG("GameObject deleted");
}

//void GameObject::Start() {
//
//}
