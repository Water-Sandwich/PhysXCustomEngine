#pragma once
#include "GameObject.h"
#include "PxDynamicObject.h"

class TestCube : public PxDynamicObject
{
public:
	TestCube(const physx::PxTransform& pose);
	void Update(float dt) override {};
	void Render() override;
};