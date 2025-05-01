#include "Cannon.h"

#include "CannonBall.h"

Cannon::Cannon(const physx::PxTransform& pose) : DynamicObject(pose)
{
	SetMaterial("steel");
	CreateShape(physx::PxBoxGeometry(1.0f, 0.3f, 1.5f), { 0.1f, 0.1f, 0.1f });
	
	auto s1 = CreateShape(physx::PxBoxGeometry(0.8f, 0.25f, 1.0f), { 0.15f, 0.15f, 0.15f });
	s1->setLocalPose(physx::PxTransform(physx::PxVec3(0, 0.55f, 0)));

	auto s2 = CreateShape(physx::PxCapsuleGeometry(0.3f, 0.75f), { 0.2f, 0.2f, 0.2f });
	s2->setLocalPose(physx::PxTransform(physx::PxVec3(0, 0.45f, 1.25f), physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 1, 0))));
	
	SetDensity(20.0f);
	InitShapes();

	physx::PxVec3 wheelPositions[4] =
	{
		physx::PxVec3(-0.8f, -0.5f, 1.2f),
		physx::PxVec3(0.8f, -0.5f, 1.2f),
		physx::PxVec3(-0.8f, -0.5f, -1.2f),
		physx::PxVec3(0.8f, -0.5f, -1.2f),
	};

	for (int i = 0; i < 4; i++)
	{
		physx::PxTransform wheelPos(wheelPositions[i]);

		Wheel* wheel = new Wheel(pose.transform(wheelPos));
		wheel->AddThis();
		wheels.push_back(wheel);

		RevoluteJoint* revoluteJoint = new RevoluteJoint((physx::PxRigidActor*)actor, wheelPos, (physx::PxRigidActor*)wheel->actor, physx::PxTransform(physx::PxVec3(0, 0, 0)));
		revoluteJoint->SetDriveVelocity(0.0f);
		/// drive limit 1k, drive gear 1f

		revoluteJoint->AddThis();
		joints.push_back(revoluteJoint);
	}
}

void Cannon::Update(float dt)
{
	float speedMult = 20.0f;

	float goalSpeed = inputdir.x * speedMult;
	for (int i = 0; i < joints.size(); i++)
	{
		float wheelSpeed = goalSpeed;

		if (inputdir.y < 0 && (i == 0 || i == 2)) // Slow left wheels when turning left
			wheelSpeed *= 0;
		if (inputdir.y > 0 && (i == 1 || i == 3)) // Slow right wheels when turning right
			wheelSpeed *= 0;

		joints[i]->SetDriveVelocity(wheelSpeed);
	}
}

void Cannon::Render()
{
	RenderShapes();
}

void Cannon::FireCannonball()
{
	physx::PxTransform mainPos = ((physx::PxRigidActor*)actor)->getGlobalPose();
	physx::PxTransform firingPos(mainPos.p + mainPos.q.rotate(physx::PxVec3(0, 0, 3.0f)));

	CannonBall* ball = new CannonBall(firingPos);
	((physx::PxRigidDynamic*)ball->actor)->setLinearVelocity(mainPos.q.rotate(physx::PxVec3(0, 0, 50.0f)));
	ball->AddThis();
}

void Cannon::onKeyDown(unsigned char c)
{
	if (c == ' ') { FireCannonball(); }

	switch (toupper(c))
	{
	case 'U':
		inputdir.x += 1;
		break;

	case 'J':
		inputdir.x -= 1;
		break;

	case 'H':
		inputdir.y += 1;
		break;

	case 'K':
		inputdir.y -= 1;
		break;
	}
}

void Cannon::onKeyUp(unsigned char c)
{
	switch (toupper(c))
	{
	case 'U':
		inputdir.x -= 1;
		break;

	case 'J':
		inputdir.x += 1;
		break;

	case 'H':
		inputdir.y -= 1;
		break;

	case 'K':
		inputdir.y += 1;
		break;
	}
}