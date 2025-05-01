#pragma once

#include "StaticObject.h"

class GameZone : public StaticObject
{
public:
	GameZone(const physx::PxTransform& pose);

	bool IsHouseCleared() const;

	virtual void Render() override;

private:
	int initialHouseParts;
	float clearPercent;
};