#include "PhysicsEngine.h"
#include "InputHandler.h"
#include <PxPhysics.h>

#include <PxActor.h>
#include <cassert>

using namespace std;
using namespace physx;

#ifdef DEBUG 
#define ASSERT_PTR(ptr);
#else 
#define ASSERT_PTR(ptr) assert(ptr != nullptr);
#endif

physx::PxFilterFlags PhysicsEngine::MyFilterShader(physx::PxFilterObjectAttributes attributesA, physx::PxFilterData filterDataA,
	physx::PxFilterObjectAttributes attributesB, physx::PxFilterData filterDataB,
	physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize)
{
	// If either object is a trigger.
	if (physx::PxFilterObjectIsTrigger(attributesA) || physx::PxFilterObjectIsTrigger(attributesB))
	{
		pairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
		return physx::PxFilterFlags();
	}

	pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;

	// Custom collision filtering handling:
	// ---

	return physx::PxFilterFlags();
}

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
	PxVisualizationParameter a;

	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true, pvd);
	ASSERT_PTR(physics);
	cooking = PxCreateCooking(PX_PHYSICS_VERSION, *foundation, PxCookingParams(PxTolerancesScale()));
	ASSERT_PTR(cooking);
	PxInitExtensions(*physics, pvd);
	

	PxSetup();
}

void PhysicsEngine::PxSetup()
{
	PxSceneDesc sceneDesc(physics->getTolerancesScale());

	if (!sceneDesc.cpuDispatcher) {
		sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
	}

	sceneDesc.filterShader = MyFilterShader;

	mainScene = physics->createScene(sceneDesc);

	ASSERT_PTR(mainScene);

	mainScene->getScenePvdClient()->setScenePvdFlags(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS | PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES | PxPvdSceneFlag::eTRANSMIT_CONTACTS);

	mainScene->setGravity(gravity);
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
	//if (InputHandler::isKeyUp('p'))
	//	return;

	//if (isPaused)
	//	return;

	mainScene->simulate(dt / 1000);
	mainScene->fetchResults(true);
}

void PhysicsEngine::CreateMaterials()
{
	materials.clear();

	CreateMaterial("testMat", .5f, .5f, .5f);

	CreateMaterial("brick", 0.6f, 0.5f, .2f);
	CreateMaterial("steel", .8f, .16f, 0.5f);
	CreateMaterial("concrete", .85f, .75f, 0.3f);
	CreateMaterial("forgedSteel", .8f, .3f, 0.7f);
	CreateMaterial("wood", .5f, .3f, 0.2f);

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

physx::PxDistanceJoint* PhysicsEngine::createDistanceJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2)
{
	return PxDistanceJointCreate(*instance->physics, actor1, frame1, actor2, frame2);
}

physx::PxFixedJoint* PhysicsEngine::createFixedJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2)
{
	return PxFixedJointCreate(*instance->physics, actor1, frame1, actor2, frame2);
}

physx::PxPrismaticJoint* PhysicsEngine::createPrismaticJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2)
{
	return PxPrismaticJointCreate(*instance->physics, actor1, frame1, actor2, frame2);
}

physx::PxRevoluteJoint* PhysicsEngine::createRevoluteJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2)
{
	return PxRevoluteJointCreate(*instance->physics, actor1, frame1, actor2, frame2);
}

physx::PxSphericalJoint* PhysicsEngine::createSphericalJoint(physx::PxRigidActor* actor1, const physx::PxTransform& frame1, physx::PxRigidActor* actor2, const physx::PxTransform& frame2)
{
	return PxSphericalJointCreate(*instance->physics, actor1, frame1, actor2, frame2);
}

physx::PxClothFabric* PhysicsEngine::createClothFabric(physx::PxClothMeshDesc* mesh, physx::PxVec3 _gravity)
{
	return PxClothFabricCreate(*instance->physics, *mesh, gravity);
}

physx::PxCloth* PhysicsEngine::createCloth(const physx::PxTransform& pose, physx::PxClothFabric* fabric, const std::vector<physx::PxClothParticle>& particles, physx::PxClothFlags flags)
{
	return instance->physics->createCloth(pose, *fabric, &particles[0], flags);
}

physx::PxShape* PhysicsEngine::createShape(const physx::PxGeometry& geometry, const physx::PxMaterial* material)
{
	return instance->physics->createShape(geometry, *material);
}

physx::PxArticulation* PhysicsEngine::createArticulation()
{
	return instance->physics->createArticulation();
}

void PhysicsEngine::addArticulation(physx::PxArticulation* art)
{
	instance->mainScene->addArticulation(*art);
}