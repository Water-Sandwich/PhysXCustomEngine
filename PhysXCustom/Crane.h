#pragma once
#include "GameObject.h"
#include "Listener.h"
#include "PxPhysicsAPI.h"
#include "StaticObject.h"
#include "DynamicObject.h"
#include "RevoluteJoint.h"
#include "Articulator.h"

class Crane : public GameObject, public Listener
{
private:
	RevoluteJoint* yaw;
	RevoluteJoint* pitch;
	float speed = 3;

public:
	void virtual onKeyDown(unsigned char c) override;
	void virtual onKeyUp(unsigned char c) override;

	Crane(const physx::PxVec3& Position);
};

class CraneBase : public DynamicObject {
public:
	CraneBase(const physx::PxVec3& Position);
	void Render() override;
};

class CraneSegment : public DynamicObject {
public:
	CraneSegment(const physx::PxVec3& Position, float length);
	void Render() override;
};

class Ball : public DynamicObject {
public:
	Ball(const physx::PxVec3& Position);
	void Render() override;
};