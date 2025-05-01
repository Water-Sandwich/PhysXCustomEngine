#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

#include "PxPhysicsAPI.h"

#include "PhysicsEngine.h"
#include "GameObject.h"
#include "StopWatch.h"
#include "Camera.h"

#include "LevelAssets.h"

//only 1 instance of this should ever exist
class Game {
private:
	inline static int w, h;
	Camera* cam;
	PhysicsEngine* physEngine;

	//queues for adding/deleting objects to objectList next frame
	std::vector<GameObject*> deleteQueue;
	std::vector<GameObject*> addQueue;
	std::vector<GameObject*> objectList;

	void DeleteObjects();
	void AddObjects();

public:
	bool _isRunning;
	inline static Game* instance;

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

	void DeleteAll();

	void Start();

	void BuildWalls();
	
	void BuildSupports(Floor* floor);

	void BuildCeiling();
};