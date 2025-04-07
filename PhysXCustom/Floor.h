#pragma once
#include "StaticObject.h"
class Floor : public StaticObject
{
public:
	Floor();
	void Update(float dt) {}
	void Render() override;
};

