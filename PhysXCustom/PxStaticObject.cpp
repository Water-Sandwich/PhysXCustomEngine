#include "PxStaticObject.h"
#include "PhysicsEngine.h"

using namespace physx;

PxStaticObject::PxStaticObject(const physx::PxTransform& pose) : PxGameObject()
{
    actor = PhysicsEngine::createStaticActor(pose);
    PhysicsEngine::AddActor(actor);
}

physx::PxShape* PxStaticObject::CreateShape(const physx::PxGeometry& geometry)
{
    return static_cast<PxRigidStatic*>(actor)->createShape(geometry, *material);
}