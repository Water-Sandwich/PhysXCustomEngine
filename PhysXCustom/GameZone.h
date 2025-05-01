#pragma once

#include "StaticObject.h"

class GameZone : public StaticObject
{
public:
	GameZone(const physx::PxTransform& pose);

	bool HousePartsInZone() const;

	void Update(float dt) override;

	virtual void Render() override;

private:
	physx::PxVec3 extents;
	int initialHouseParts;
	float clearPercent;
};