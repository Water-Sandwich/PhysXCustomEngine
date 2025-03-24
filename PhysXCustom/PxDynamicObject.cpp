#include "PxDynamicObject.h"
#include "PhysicsEngine.h"

using namespace physx;

PxDynamicObject::PxDynamicObject(const physx::PxTransform& pose) : PxGameObject()
{
    actor = PhysicsEngine::createDynamicActor(pose);
    PhysicsEngine::AddActor(actor);
}

physx::PxShape* PxDynamicObject::CreateShape(const physx::PxGeometry& geometry)
{
    return static_cast<PxRigidDynamic*>(actor)->createShape(geometry, *material);
}

void PxDynamicObject::SetDensity(physx::PxReal density)
{
    physx::PxRigidBodyExt::updateMassAndInertia(*static_cast<PxRigidDynamic*>(actor), density);
}