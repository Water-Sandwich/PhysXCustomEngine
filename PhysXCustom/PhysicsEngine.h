#pragma once

#include "PxPhysicsAPI.h"
#include <map>
#include <string>

class PhysicsEngine
{
private:
	//PHYSX
	physx::PxDefaultErrorCallback gDefaultErrorCallback;
	physx::PxDefaultAllocator gDefaultAllocatorCallback;

	physx::PxFoundation* foundation = nullptr;
	physx::PxPvd* pvd = nullptr;
	physx::PxPhysics* physics = nullptr;
	physx::PxCooking* cooking = nullptr;
	physx::PxScene* mainScene = nullptr;

	std::map<std::string, physx::PxMaterial*> materials;

	inline static PhysicsEngine* instance = nullptr;

public:
	PhysicsEngine();
	~PhysicsEngine();

	static void AddActor(physx::PxActor* actor);
	static void RemoveActor(physx::PxActor* actor);

	void PxInit();
	void PxSetup();
	void PxClean();

	void CreateMaterials();
	physx::PxMaterial* CreateMaterial();
	static physx::PxMaterial* GetMaterial(std::string name);

	static physx::PxActor* createStaticActor(const physx::PxTransform& pose);
	static physx::PxActor* createDynamicActor(const physx::PxTransform& pose);
};