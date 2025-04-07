#include "PxStaticObject.h"
#include "PhysicsEngine.h"
#include "UserData.h"

using namespace physx;

PxStaticObject::PxStaticObject(const physx::PxTransform& pose) : PxGameObject()
{
    actor = PhysicsEngine::createStaticActor(pose);
    PhysicsEngine::AddActor(actor);
}

physx::PxShape* PxStaticObject::CreateShape(const physx::PxGeometry& geometry, const physx::PxVec3& colour)
{
    auto s = static_cast<PxRigidStatic*>(actor)->createShape(geometry, *material);
    s->userData = new UserData(colour);
    return s;
}