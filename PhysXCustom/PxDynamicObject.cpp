#include "PxDynamicObject.h"
#include "PhysicsEngine.h"
#include "UserData.h"

using namespace physx;

PxDynamicObject::PxDynamicObject(const physx::PxTransform& pose) : PxGameObject()
{
    actor = PhysicsEngine::createDynamicActor(pose);
    PhysicsEngine::AddActor(actor);
}

physx::PxShape* PxDynamicObject::CreateShape(const physx::PxGeometry& geometry, const physx::PxVec3& colour)
{
    auto s = static_cast<PxRigidDynamic*>(actor)->createShape(geometry, *material);
    s->userData = new UserData(colour);
    static_cast<PxRigidActor*>(actor)->attachShape(*s);
    return s;
}

void PxDynamicObject::SetDensity(physx::PxReal density)
{
    physx::PxRigidBodyExt::updateMassAndInertia(*static_cast<PxRigidDynamic*>(actor), density);
}