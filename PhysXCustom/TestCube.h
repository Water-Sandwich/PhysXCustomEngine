#pragma once
#include "GameObject.h"
#include "DynamicObject.h"

class TestCube : public DynamicObject
{
public:
	TestCube(const physx::PxTransform& pose);
	void Update(float dt) override {};
	void Render() override;
};