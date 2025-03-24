#include <algorithm>
#include <ranges>
#include <GL/freeglut.h>
#include <fstream>
#include <sstream>
#include <thread>
#include <iostream>

#include "Game.h"
#include "InputHandler.h"
#include <PxActor.h>
#include "TestCube.h"
using namespace physx;

//Game has an addList and deleteList. the most important list is objectList
//these are to mark objects to be added or removed from objectList
//deleteObjects is much more complicated, powered by magic(tm)
//essentially, it removes the object from objectlist, frees it from memory, sets it to null and clears it from the list
//its this bad because some objects may create other objects when deleted

//GAME STATE FLOW
//main() -> Game() -> Game::Start() -> Game::StartGame() -> Cannon() -> Game::End() -> Game::Start()

Game::Game(const std::string& title, int x, int y) {
	//make sure theres only 1 instance of game, otherwise it likes to crash
	filePath = std::filesystem::current_path() / "leaderboard.txt";

	if (!instance) {
		instance = this;
	}
	else {
		//cant make 2 games
		throw "ERROR: Creating 2 games";
	}
	_isRunning = true;

	//sometimes crashes if i dont reserve space
	objectList.reserve(512);
	cam = new Camera();
	AddObject(cam);

	//more GLUT init
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(x, y);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(title.c_str());

	// Setup lighting
	glEnable(GL_LIGHTING);
	PxReal ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.f };
	PxReal diffuseColor[] = { 0.7f, 0.7f, 0.7f, 1.f };
	PxReal position[] = { 50.f, 50.f, 100.f, 0.f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);

	physEngine = new PhysicsEngine();
	physEngine->PxInit();

	Start();
}

//game cleanup on close
Game::~Game() {
	_isRunning = false;

	//delete objects until there is nothing left, makes sure everything is cleaned
	while (objectList.size() != 0) {
		AddObjects();
		std::ranges::for_each(objectList, [](GameObject* a) { a->DeleteThis(); });
		DeleteObjects();
	}

	physEngine->PxClean();

	instance = nullptr;
}

void Game::DeleteAll() {
	for (auto obj : objectList)
		obj->DeleteThis();
}


void Game::Start() {
	DeleteAll();
	AddObject(new TestCube());
}

void Game::StartGame() {
	Game::instance->DeleteAll();


}

void Game::End() {
	DeleteAll();

}

std::stringstream Game::readFromFile() {
	std::ifstream file(instance->filePath);
	if (!file.is_open()) {
		std::ofstream temp(instance->filePath);
		temp.close();
		printf("COULD NOT OPEN LEADERBOARD, CREATING FILE\n");
		fflush(stdout);
		return std::stringstream();
	}
	std::stringstream ss;
	std::string str;

	while (std::getline(file, str)) {
		ss << str << std::endl;
	}

	file.close();
	return ss;
}

//calls update on every GameObject
void Game::Update(float deltaTime) {
	AddObjects();
	DeleteObjects();
	for (auto object : objectList)
		object->Update(deltaTime);
}
float a = 0;
//calls render on every GameObject
void Game::Render() {
	glClearColor(0, 0.1, 0.1, 1); //backround color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Setup camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.f, (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT), 1.f, 10000.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam->pos.x, cam->pos.y, cam->pos.z,
		cam->pos.x + cam->dir.x, cam->pos.y + cam->dir.y, cam->pos.z + cam->dir.z, 0, 1, 0);

	for (auto obj : objectList) {

	
		obj->Render();
	}

	glutSwapBuffers();
}

bool Game::isRunning() const {
	return _isRunning;
}

//mark to add object next frame, returns the pointer to where the object is stored
GameObject* Game::AddObject(GameObject* obj) {
	instance->addQueue.push_back(obj);
	return obj;
}


//will cause issues if objects create objects on start
void Game::AddObjects() {
	if (addQueue.empty())
		return;

	for (auto& obj : addQueue) {
		//obj->Start();
		objectList.push_back(obj);
	}

	addQueue.clear();
}

//deletes and frees objects in deleteQueue from memory
void Game::DeleteObjects() {
	if (deleteQueue.empty())
		return;

	//cannot pass deleteQueue directly to lambda
	auto& queue = deleteQueue;

	//have to remove duplicates. may happen due to projectile hitting 2 things at once
	std::ranges::sort(queue);
	queue.erase(std::ranges::unique(queue).begin(), queue.end());

	while (!queue.empty()) {
		//remove nulls
		std::erase_if(
			queue,
			[](GameObject*& a) { return a == nullptr; }
		);

		//remove matching objects that are in del and objectlist from objectlist
		std::erase_if(
			objectList,
			[queue](GameObject*& a) { return std::ranges::find(queue, a) != queue.end(); }
		);

		//delete all in queue
		int size = queue.size();
		for (int i = 0; i < size; i++) {
			delete queue[i];
			queue[i] = nullptr;
			size = queue.size();
		}
	}
}

//mark to remove object next frame
void Game::DeleteObject(GameObject* obj) {
	instance->deleteQueue.push_back(obj);
}