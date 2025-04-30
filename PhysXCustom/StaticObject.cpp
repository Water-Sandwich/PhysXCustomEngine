#include "StaticObject.h"
#include "PhysicsEngine.h"
#include "UserData.h"

using namespace physx;

StaticObject::StaticObject(const physx::PxTransform& pose) : PxGameObject()
{
    actor = PhysicsEngine::createStaticActor(pose);
    PhysicsEngine::AddActor(actor);
}

physx::PxShape* StaticObject::CreateShape(const physx::PxGeometry& geometry, const physx::PxVec3& colour)
{
    auto s = static_cast<PxRigidStatic*>(actor)->createShape(geometry, *material);
    s->userData = new UserData(colour);
    //static_cast<PxRigidActor*>(actor)->attachShape(*s);
    return s;
}