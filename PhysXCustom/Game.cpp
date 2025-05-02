#include <algorithm>
#include <ranges>
#include <GL/freeglut.h>
#include <fstream>
#include <sstream>
#include <thread>
#include <iostream>

#include "Game.h"
#include "Renderer.h"
#include "InputHandler.h"
#include <PxActor.h>

#include "LevelAssets.h"

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

	Renderer::Setup(x, y, title.c_str());

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

	Floor* floor = new Floor();
	AddObject(floor);

	BuildWalls();
	BuildSupports(floor);
	BuildCeiling();

	GameZone* gameZone = new GameZone({ 0, 0, 0 });
	AddObject(gameZone);

	Cannon* cannon = new Cannon({ 0, 1, -50 });
	AddObject(cannon);
}

//calls update on every GameObject
void Game::Update(float deltaTime) {
	AddObjects();
	DeleteObjects();

	physEngine->Update(deltaTime);

	for (auto object : objectList)
		object->Update(deltaTime);
}

// essential.
float a = 0;

//calls render on every GameObject
void Game::Render() {
	Renderer::Start();
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

void Game::BuildWalls()
{
	// brick information
	float sizeX = 1.0f;
	float sizeY = 0.5f;
	float sizeZ = 0.5f;

	// wall information
	int bricksLength = 15;
	int bricksHeight = 5; // Should always be a multiple of 5.
	float wallLength = (bricksLength * sizeX);

	for (int wall = 0; wall < 4; wall++)
	{
		float rot = wall * (PxPi / 2.0f);
		PxQuat wallRot(rot, PxVec3(0, 1, 0));

		PxVec3 wallPos;
		switch (wall) {
		case 0: wallPos = PxVec3(0, 0, wallLength / 2.0f + sizeZ / 2.0f); break;
		case 1: wallPos = PxVec3(wallLength / 2.0f + sizeZ / 2.0f, 0, 0); break;
		case 2: wallPos = PxVec3(0, 0, -(wallLength / 2.0f + sizeZ / 2.0f)); break;
		case 3: wallPos = PxVec3(-(wallLength / 2.0f + sizeZ / 2.0f), 0, 0); break; }

		PxTransform wallTransform(wallPos, wallRot);

		for (int row = 0; row < bricksHeight; row++)
		{
			float brickPosY = (row * sizeY) + (sizeY / 2.0f);
			bool doOffset = (row % 2 != 0);
			doOffset ^= (wall == 1 || wall == 3);
			const int offset = doOffset ? 1 : 0;

			for (int col = 0; col < bricksLength + offset; col++)
			{
				float brickPosX;

				if (doOffset) { brickPosX = (-wallLength / 2.0f) + (col * sizeX); }
				else { brickPosX = (-wallLength / 2.0f) + ((col + 0.5f) * sizeX); }

				PxVec3 brickPos(brickPosX, brickPosY, 0.0f);
				PxTransform brickTransform = wallTransform.transform(PxTransform(brickPos));
				ConcreteBlock* brick = new ConcreteBlock(brickTransform);
				AddObject(brick);
			}
		}
	}
}

void Game::BuildSupports(Floor* floor)
{
	float sizeX = 0.4f;
	float sizeY = 2.5f;
	float sizeZ = 0.4f;

	int bricksLength = 15;
	int bricksHeight = 5;

	float wallLength = bricksLength * 1.0f;

	for (int wall = 0; wall < 8; wall++)
	{
		float rot = wall * (PxPi / 2.0f);
		PxQuat wallRot(rot, PxVec3(0, 1, 0));

		PxVec3 wallPos;
		switch (wall) {
		case 0: wallPos = PxVec3(0, 0, wallLength / 2.0f + .7f); break;
		case 1: wallPos = PxVec3(wallLength / 2.0f + .7f, 0, 0); break;
		case 2: wallPos = PxVec3(0, 0, -(wallLength / 2.0f + .7f)); break;
		case 3: wallPos = PxVec3(-(wallLength / 2.0f + .7f), 0, 0); break;
		case 4: wallPos = PxVec3(0, 0, wallLength / 2.0f - sizeZ / 2.0f); break;
		case 5: wallPos = PxVec3(wallLength / 2.0f - sizeZ / 2.0f, 0, 0); break;
		case 6: wallPos = PxVec3(0, 0, -(wallLength / 2.0f - sizeZ / 2.0f)); break;
		case 7: wallPos = PxVec3(-(wallLength / 2.0f - sizeZ / 2.0f), 0, 0); break; }

		PxTransform wallTransform(wallPos, wallRot);

		for (int row = 0; row < bricksHeight; row += 5)
		{
			float beamPosY = (row * 0.5f) + (sizeY / 2.0f);

			for (int col = 0; col < bricksLength; col += 5)
			{
				float beamPosX = (-wallLength / 2.0f) + col + 0.5f;

				PxVec3 beamPos(beamPosX, beamPosY, 0.0f);
				PxTransform beamTransform = wallTransform.transform(PxTransform(beamPos));
				SteelBeam* beam = new SteelBeam(beamTransform);
				AddObject(beam);

				PxTransform beamAnchor = PxTransform(PxIdentity);
				PxTransform floorAchor = (((PxRigidActor*)floor->actor)->getGlobalPose()).getInverse() * beamTransform;

				FixedJoint* fixedJoint = new FixedJoint((PxRigidActor*)beam->actor, beamAnchor, (PxRigidActor*)floor->actor, floorAchor);
				fixedJoint->SetBreakable(500000.0f, 500000.0f);
				AddObject(fixedJoint);
			}
		}
	}
}

void Game::BuildCeiling()
{
	int gridCount = 9;
	
	float roofHeight = 3.0f;
	float roofWidth = 18.0f;

	float cellSize = roofWidth / gridCount;

	std::vector<std::vector<GlassPanel*>> roofPanels(gridCount, std::vector<GlassPanel*>(gridCount, nullptr));

	for (int i = 0; i < gridCount; i++)
	{
		for (int j = 0; j < gridCount; j++)
		{
			float panelPosX = (-roofWidth / 2) + (cellSize / 2) + (j * cellSize);
			float panelPosZ = (-roofWidth / 2) + (cellSize / 2) + (i * cellSize);
			PxVec3 panelPos(panelPosX, roofHeight, panelPosZ);
			PxTransform panelTransform(panelPos);

			GlassPanel* panel = new GlassPanel(panelTransform);
			AddObject(panel);
			roofPanels[i][j] = panel;
		}
	}

	for (int i = 0; i < gridCount; i++)
	{
		for (int j = 0; j < gridCount; j++)
		{
			GlassPanel* currentPanel = roofPanels[i][j];
			PxTransform currentPanelTransform = ((PxRigidActor*)currentPanel->actor)->getGlobalPose();

			if (j < gridCount - 1)
			{
				GlassPanel* rightPanel = roofPanels[i][j + 1];
				PxTransform rightPanelTransform = ((PxRigidActor*)rightPanel->actor)->getGlobalPose();

				PxVec3 jointPos = (currentPanelTransform.p + rightPanelTransform.p) * 0.5f;
				PxTransform currentAnchor = currentPanelTransform.getInverse() * PxTransform(jointPos);
				PxTransform rightAnchor = rightPanelTransform.getInverse() * PxTransform(jointPos);

				FixedJoint* fixedJoint = new FixedJoint((PxRigidActor*)currentPanel->actor, currentAnchor, (PxRigidActor*)rightPanel->actor, rightAnchor);
				fixedJoint->SetBreakable(50000.0f, 50000.0f);
				AddObject(fixedJoint);
			}

			if (i < gridCount - 1)
			{
				GlassPanel* frontPanel = roofPanels[i + 1][j];
				PxTransform frontPanelTransform = ((PxRigidActor*)frontPanel->actor)->getGlobalPose();

				PxVec3 jointPos = (currentPanelTransform.p + frontPanelTransform.p) * 0.5f;
				PxTransform currentAnchor = currentPanelTransform.getInverse() * PxTransform(jointPos);
				PxTransform frontAnchor = frontPanelTransform.getInverse() * PxTransform(jointPos);

				FixedJoint* fixedJoint = new FixedJoint((PxRigidActor*)currentPanel->actor, currentAnchor, (PxRigidActor*)frontPanel->actor, frontAnchor);
				fixedJoint->SetBreakable(75000.0f, 75000.0f);
				AddObject(fixedJoint);
			}
		}
	}
}