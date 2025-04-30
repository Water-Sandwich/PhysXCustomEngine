#pragma once

#include "PxGameObject.h"
#include <PxPhysicsAPI.h>

class Articulator : public PxGameObject
{
private:
	physx::PxArticulation* articulator;
	physx::PxShape* shape;
	physx::PxVec3 color;

	std::vector<physx::PxArticulationLink*> links;
	std::vector<physx::PxArticulationJoint*> joints;

public:
	Articulator(const physx::PxGeometry& geometry, const physx::PxMaterial* mat, const physx::PxVec3& color);
	void Render() override;
	void AddLink(const physx::PxTransform& pose, float mass, float distanceBetweenJoints);
	void AddLinks(physx::PxTransform startPose, const physx::PxVec3& direction, float mass, int numLinks);
	void AddArticulator();
	
	physx::PxArticulationLink* getFirstLink();
	physx::PxArticulationLink* getLastLink();

	void Update(float dt) override {};
	virtual physx::PxShape* CreateShape(const physx::PxGeometry& geom, const physx::PxVec3& col) { return nullptr; };
};

