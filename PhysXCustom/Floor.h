#pragma once
#include "PxStaticObject.h"
class Floor : public PxStaticObject
{
public:
	Floor();
	void Update(float dt) {}
	void Render() override;
};

