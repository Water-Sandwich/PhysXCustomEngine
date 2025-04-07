#include "PhysicsEngine.h"
#include "InputHandler.h"

#include <PxActor.h>
#include <cassert> //TODO: Remove asserts for release build

using namespace std;
using namespace physx;

#define ASSERT_PTR(ptr) assert(ptr != nullptr);

PhysicsEngine::PhysicsEngine()
{
	if (instance)
		throw ("creating multiple = bad :(");
	
	instance = this;
}

PhysicsEngine::~PhysicsEngine()
{
	instance = nullptr;
}

void PhysicsEngine::AddActor(physx::PxActor* actor)
{
	instance->mainScene->addActor(*actor);
}

void PhysicsEngine::RemoveActor(physx::PxActor* actor)
{
	instance->mainScene->removeActor(*actor);
}

void PhysicsEngine::PxInit() {
	foundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
	ASSERT_PTR(foundation);

	pvd = PxCreatePvd(*foundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("localhost", 5425, 10);
	pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);
	ASSERT_PTR(pvd);

	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true, pvd);
	ASSERT_PTR(physics);
	cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, PxCookingParams(PxTolerancesScale()));
	ASSERT_PTR(cooking);

	PxSetup();
}

void PhysicsEngine::PxSetup()
{
	PxSceneDesc sceneDesc(physics->getTolerancesScale());

	if (!sceneDesc.cpuDispatcher) {
		sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
	}

	sceneDesc.filterShader = PxDefaultSimulationFilterShader;

	mainScene = physics->createScene(sceneDesc);

	if (!mainScene)
		throw "Main Scene failed to init";

	mainScene->setGravity({ 10,-9.81,0 });
	CreateMaterials();
}

void PhysicsEngine::PxClean() {
	if (cooking)
		cooking->release();
	if (physics)
		physics->release();
	if (pvd)
		pvd->release();
	if (foundation)
		foundation->release();
}

void PhysicsEngine::Update(float dt)
{
	//TODO: Input checking is dogshit, i miss SDL input every day
	if (InputHandler::isKeyUp('p'))
		return;

	//if (isPaused)
	//	return;

	mainScene->simulate(dt / 1000);
	mainScene->fetchResults(true);
}

void PhysicsEngine::CreateMaterials()
{
	materials.clear();

	CreateMaterial("testMat", .5f, .5f, .5f);

	// further materials can be added here
}

void PhysicsEngine::CreateMaterial(string name, PxReal staticFriction, PxReal dynamicFriction, PxReal restitution)
{
	materials.insert({ name, physics->createMaterial(staticFriction, dynamicFriction, restitution) });
}

PxMaterial* PhysicsEngine::GetMaterial(string name)
{
	return instance->materials.at(name);
}

physx::PxActor* PhysicsEngine::createStaticActor(const physx::PxTransform& pose)
{
	return instance->physics->createRigidStatic(pose);
}

physx::PxActor* PhysicsEngine::createDynamicActor(const physx::PxTransform& pose)
{
	return instance->physics->createRigidDynamic(pose);
}

physx::PxFixedJoint* PhysicsEngine::createFixedJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2)
{
	return PxFixedJointCreate(*instance->physics, actor1, frame1, actor2, frame2);
}
