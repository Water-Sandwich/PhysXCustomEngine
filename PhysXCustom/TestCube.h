#pragma once
#include "GameObject.h"
#include "PxDynamicObject.h"

class TestCube : public PxDynamicObject
{
public:
	TestCube();
	void Update(float dt) override {};
	void Render() override;
};

