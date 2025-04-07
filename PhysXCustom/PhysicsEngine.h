#pragma once

#include "PxPhysicsAPI.h"
#include "ErrorCallback.h"
#include <map>
#include <string>

class PhysicsEngine
{
private:
	//PHYSX
	ErrorCallback gDefaultErrorCallback;
	physx::PxDefaultAllocator gDefaultAllocatorCallback;

	physx::PxFoundation* foundation = nullptr;
	physx::PxPvd* pvd = nullptr;
	physx::PxPhysics* physics = nullptr;
	physx::PxCooking* cooking = nullptr;
	physx::PxScene* mainScene = nullptr;
	//TODO: MAKE A CALLBACK CLASS?

	std::map<std::string, physx::PxMaterial*> materials;

	inline static PhysicsEngine* instance = nullptr;
	bool isPaused = true;

public:
	PhysicsEngine();
	~PhysicsEngine();

	static void AddActor(physx::PxActor* actor);
	static void RemoveActor(physx::PxActor* actor);

	void PxInit();
	void PxSetup();
	void PxClean();
	void Update(float dt);

	void CreateMaterials();
	void CreateMaterial(std::string name = "default", physx::PxReal staticFriction = .0f, physx::PxReal dynamicFriction = .0f, physx::PxReal restitution = .0f);
	static physx::PxMaterial* GetMaterial(std::string name);

	static physx::PxActor* createStaticActor(const physx::PxTransform& pose);
	static physx::PxActor* createDynamicActor(const physx::PxTransform& pose);

	static physx::PxFixedJoint* createFixedJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2);
};