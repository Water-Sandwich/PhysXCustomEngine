#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

#include "PxPhysicsAPI.h"

#include "Rect.h"
#include "GameObject.h"
#include "Vector2.h"
#include "StopWatch.h"
#include "Color.h"
#include "Camera.h"

//only 1 instance of this should ever exist
class Game {
private:
	inline static int w, h;
	std::filesystem::path filePath;
	Camera* cam;

	//queues for adding/deleting objects to objectList next frame
	std::vector<GameObject*> deleteQueue;
	std::vector<GameObject*> addQueue;
	std::vector<GameObject*> objectList;

	//PHYSX
	physx::PxDefaultErrorCallback gDefaultErrorCallback;
	physx::PxDefaultAllocator gDefaultAllocatorCallback;

	physx::PxFoundation* foundation = nullptr;
	physx::PxPvd* pvd = nullptr;
	physx::PxPhysics* physics = nullptr;
	physx::PxCooking* cooking = nullptr;
	physx::PxScene* mainScene = nullptr;

	void PxInit();
	void PxSetup();
	void PxClean();

	void DeleteObjects();

	void AddObjects();

public:
	bool _isRunning;
	inline static Game* instance;

	void AddActor(physx::PxActor* actor);
	void RemoveActor(physx::PxActor* actor);

	void Update(float deltaTime);

	void Render();

	bool isRunning() const;

	static GameObject* AddObject(GameObject* obj);

	//marks object for deletion on the next frame.
	static void DeleteObject(GameObject* obj);

	Game(const std::string& title, int x, int y);

	Game(Game& t) = delete;

	~Game();

	int listSize() const { return objectList.size(); };

	static void renderText(float x, float y, std::string text, Color color, bool center = true);

	void DeleteAll();

	void Start();

	void StartGame();
	
	void End();

	static std::stringstream readFromFile();
};
