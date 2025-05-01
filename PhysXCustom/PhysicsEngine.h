#pragma once

#include "PxPhysicsAPI.h"
#include "ErrorCallback.h"
#include <map>
#include <string>
#include <vector>

class PhysicsEngine
{
private:
	//PHYSX
	ErrorCallback gDefaultErrorCallback;
	physx::PxDefaultAllocator gDefaultAllocatorCallback;
	inline static const physx::PxVec3 gravity = { 0,-9.81,0 };

	physx::PxFoundation* foundation = nullptr;
	physx::PxPvd* pvd = nullptr;
	physx::PxPhysics* physics = nullptr;
	physx::PxCooking* cooking = nullptr;
	physx::PxScene* mainScene = nullptr;
	physx::PxPvdTransport* transport = nullptr;

	std::map<std::string, physx::PxMaterial*> materials;

	inline static PhysicsEngine* instance = nullptr;
	bool isPaused = true;

	static physx::PxFilterFlags MyFilterShader(
		physx::PxFilterObjectAttributes attributesA, physx::PxFilterData filterDataA,
		physx::PxFilterObjectAttributes attributesB, physx::PxFilterData filterDataB,
		physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize);


public:
	PhysicsEngine();
	~PhysicsEngine();

	static void AddActor(physx::PxActor* actor);
	static void RemoveActor(physx::PxActor* actor);
	static const physx::PxScene* GetScene();

	void PxInit();
	void PxSetup();
	void PxClean();
	void Update(float dt);

	void CreateMaterials();
	void CreateMaterial(std::string name = "default", physx::PxReal staticFriction = .0f, physx::PxReal dynamicFriction = .0f, physx::PxReal restitution = .0f);
	static physx::PxMaterial* GetMaterial(std::string name);

	static physx::PxActor* createStaticActor(const physx::PxTransform& pose);
	static physx::PxActor* createDynamicActor(const physx::PxTransform& pose);

	static physx::PxDistanceJoint* createDistanceJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2);
	static physx::PxFixedJoint* createFixedJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2);
	static physx::PxPrismaticJoint* createPrismaticJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2);
	static physx::PxRevoluteJoint* createRevoluteJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2);
	static physx::PxSphericalJoint* createSphericalJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2);
	static physx::PxClothFabric* createClothFabric(physx::PxClothMeshDesc* mesh, physx::PxVec3 _gravity = gravity);
	static physx::PxCloth* createCloth(const physx::PxTransform& pose, physx::PxClothFabric* fabric, const std::vector<physx::PxClothParticle>& particles, physx::PxClothFlags flags = physx::PxClothFlags());
	static physx::PxShape* createShape(const physx::PxGeometry& geometry, const physx::PxMaterial* material);
	static physx::PxArticulation* createArticulation();
	static void addArticulation(physx::PxArticulation* art);
};