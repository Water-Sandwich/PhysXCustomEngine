#pragma once

#include "DynamicObject.h"
#include "Listener.h"
#include "Wheel.h"
#include "RevoluteJoint.h"


class Cannon : public DynamicObject, public Listener
{
private:
	physx::PxVec2 inputdir;

	std::vector<Wheel*> wheels;
	std::vector<RevoluteJoint*> joints;

public:
	Cannon(const physx::PxTransform& pose);
	void Update(float dt) override;
	void Render() override;
	void FireCannonball();

	void virtual onKeyDown(unsigned char c);
	void virtual onKeyUp(unsigned char c);
};