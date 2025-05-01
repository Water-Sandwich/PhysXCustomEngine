#include "GameZone.h"
#include "PhysicsEngine.h"

GameZone::GameZone(const physx::PxTransform& pose) : StaticObject(pose)
{
	SetMaterial("testMat");
	CreateShape(physx::PxBoxGeometry(10.0f, 10.0f, 10.0f), { 0, 0, 0.5 });
	extents = physx::PxVec3(10.0f, 10.0f, 10.0f);
	InitShapes();

	SetTrigger(true);
	SetFilters(Layer::GameZone, Layer::House);

	const physx::PxScene* scene = PhysicsEngine::GetScene();
	physx::PxBoxGeometry boxGeom(extents.x, extents.y, extents.z);
	physx::PxTransform zoneTransform = ((physx::PxRigidActor*)actor)->getGlobalPose();

	physx::PxOverlapHit hitBuffer[500];
	physx::PxOverlapBuffer overlapBuffer(hitBuffer, 500);
	initialHouseParts = 0;
	clearPercent = .50f;

	if (scene->overlap(boxGeom, zoneTransform, overlapBuffer))
	{
		for (physx::PxU32 i = 0; i < overlapBuffer.getNbTouches(); i++)
		{
			const physx::PxOverlapHit& hit = overlapBuffer.getTouches()[i];
			physx::PxFilterData fd = hit.shape->getSimulationFilterData();
			if (fd.word0 & (int)Layer::House)
			{
				initialHouseParts += 1;
			}
		}
	}
}

bool GameZone::HousePartsInZone() const
{
	const physx::PxScene* scene = PhysicsEngine::GetScene();
	physx::PxBoxGeometry boxGeom(extents.x, extents.y, extents.z);
	physx::PxTransform zoneTransform = ((physx::PxRigidActor*)actor)->getGlobalPose();

	physx::PxOverlapHit hitBuffer[500];
	physx::PxOverlapBuffer overlapBuffer(hitBuffer, 500);
	int houseParts = 0;

	if (scene->overlap(boxGeom, zoneTransform, overlapBuffer))
	{
		for (physx::PxU32 i = 0; i < overlapBuffer.getNbTouches(); i++)
		{
			const physx::PxOverlapHit& hit = overlapBuffer.getTouches()[i];
			physx::PxFilterData fd = hit.shape->getSimulationFilterData();
			if (fd.word0 & (int)Layer::House)
			{
				houseParts += 1;
			}
		}
	}

	if (initialHouseParts == 0) { return true; }

	float cleared = (float)houseParts / (float)initialHouseParts;
	std::cout << (int)(cleared * 100) << "% remaining!" << std::endl;

	return (cleared <= (1.0f - clearPercent));
}

void GameZone::Update(float dt)
{
	if (HousePartsInZone()) { std::cout << "Victory condition met!!!Congratulations." << std::endl; }
}

void GameZone::Render()
{
	//RenderShapes();
}