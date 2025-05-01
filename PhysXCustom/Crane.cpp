#include "Crane.h"
#include "HouseFloor.h"

#include "RevoluteJoint.h"
#include "PhysicsEngine.h"
#include "DistanceJoint.h"
#include "Cloth.h"

using namespace physx;

void Crane::onKeyDown(unsigned char c)
{
	c = toupper(c);
	if (c == 'U')
		pitch->SetDriveVelocity(speed);
	if (c == 'J')
		pitch->SetDriveVelocity(-speed);
	if (c == 'H')
		yaw->SetDriveVelocity(speed);
	if (c == 'K')
		yaw->SetDriveVelocity(-speed);
}

void Crane::onKeyUp(unsigned char c)
{
	c = toupper(c);
	if (c == 'U')
		pitch->SetDriveVelocity(0);
	if (c == 'J')
		pitch->SetDriveVelocity(0);
	if (c == 'H')
		yaw->SetDriveVelocity(0);
	if (c == 'K')
		yaw->SetDriveVelocity(0);
}

Crane::Crane(const physx::PxVec3& Position)
{
	auto pos = Position;

	pos.y += 0.5;
	auto base = new CraneBase(Position);
	base->AddThis();

	//pos.y += 7.5;
	auto segment1 = new CraneSegment(pos, 15);
	segment1->AddThis();

	pos.y += 12;
	auto segment2 = new CraneSegment(pos, 12);
	segment2->AddThis();

	auto i = PxQuat(PxIdentity);
	auto rot = PxQuat(PxHalfPi, {0,0,1});
	auto up = rot * i;
	auto down = -up;
	auto left = PxQuat(PxHalfPi, { 1,0,0 }) * i;
	auto right = -left;

	yaw = new RevoluteJoint(base, PxTransform({ 0,0,0 }, up), segment1, PxTransform({ 0,-15, 0 }, down));
	yaw->AddThis();
	yaw->SetDriveVelocity(0);

	pitch = new RevoluteJoint(segment1, PxTransform({ 0,15,0 }, left), segment2, PxTransform({ 0,-12, 0 }, right));
	pitch->AddThis();
	pitch->SetDriveVelocity(0);

	pos.x -= 6;
	auto art = new Articulator(PxSphereGeometry(2), PhysicsEngine::GetMaterial("forgedSteel"), { 0,0,0 });
	art->AddLinks(PxTransform(pos, left), { -6,0,0 }, 30, 7);
	art->AddArticulator();
	art->AddThis();

	auto j1 = new DistanceJoint((PxRigidDynamic*)segment2->actor, PxTransform({ 0,12, 0 }, up), art->getFirstLink(), PxTransform(PxIdentity));
	j1->AddThis();

	//auto ball = new Ball(art->getLastLink()->getGlobalPose().p);
	//ball->AddThis();
	//auto j2 = new DistanceJoint((PxRigidDynamic*)art->getLastLink(), PxTransform(PxIdentity), (PxRigidDynamic*)ball, PxTransform(PxIdentity));
	//j2->AddThis();
}

CraneBase::CraneBase(const physx::PxVec3& Position) : DynamicObject(PxTransform(Position))
{
	SetMaterial("steel");
	CreateShape(physx::PxBoxGeometry(5,0.5,5), { 0, 0, 1 });
	SetDensity(10000);
	InitShapes();
}

void CraneBase::Render()
{
	RenderShapes();
}

CraneSegment::CraneSegment(const physx::PxVec3& Position, float length) : DynamicObject(PxTransform(Position))
{
	SetMaterial("steel");
	CreateShape(physx::PxBoxGeometry(2, length, 2), { 0.2f, 0.2f, 0 });
	CreateShape(physx::PxBoxGeometry(3,3,3), { 0.2f, 0.2f, 0 });
	SetDensity(8.05);
	InitShapes();
}

void CraneSegment::Render()
{
	RenderShapes();
}

Ball::Ball(const physx::PxVec3& Position) : DynamicObject(PxTransform(Position))
{
	SetMaterial("forgedSteel");
	CreateShape(physx::PxSphereGeometry(4),  { 0.2f, 0.2f, 0 });
	SetDensity(1);
	InitShapes();
}

void Ball::Render()
{
	RenderShapes();
}
