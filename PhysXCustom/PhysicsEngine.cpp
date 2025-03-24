#include "PhysicsEngine.h"
#include <PxActor.h>

using namespace physx;

PhysicsEngine::PhysicsEngine()
{
	if (instance)
	{
		throw ("creating multiple = bad :(");
	}
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

	pvd = PxCreatePvd(*foundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("localhost", 5425, 10);
	pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true, pvd);
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

	mainScene->setGravity({ 0,-10,0 });
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

void PhysicsEngine::CreateMaterials()
{
}

PxMaterial* PhysicsEngine::CreateMaterial()
{
	return nullptr;
}

PxMaterial* PhysicsEngine::GetMaterial(std::string name)
{
	return nullptr;
}