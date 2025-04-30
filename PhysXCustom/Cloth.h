#pragma once
#include "PxGameObject.h"
#include "cloth/PxCloth.h"
#include <vector>
#include <PxPhysicsAPI.h>

struct Vec4I {
	physx::PxU32 x, y, z, w;
};

class Cloth : public PxGameObject
{
private:
	std::vector<physx::PxClothParticle> particles;
	std::vector<Vec4I> quads;
	physx::PxClothMeshDesc mesh;
	physx::PxClothFabric* fabric = nullptr;
	physx::PxVec3 color;
	int particlesSize;
	int quadsSize;

public:
	Cloth(const physx::PxTransform& pose, const physx::PxVec2& size, const physx::PxVec2& subDivisions, const physx::PxVec3& colour);
	void Render() override;

	const std::vector<physx::PxClothParticle>* getParticles() const;
	const std::vector<Vec4I>* getQuads() const;
	physx::PxVec3* getColor() const;
	const physx::PxClothMeshDesc* getMesh() const;

	void Update(float dt) override {};
	virtual physx::PxShape* CreateShape(const physx::PxGeometry& geom, const physx::PxVec3& col) override { return nullptr; };
};

