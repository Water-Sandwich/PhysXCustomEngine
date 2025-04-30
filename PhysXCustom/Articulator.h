#pragma once

#include "PxGameObject.h"
#include <PxPhysicsAPI.h>

class Articulator : public PxGameObject
{
private:
	physx::PxArticulation* articulator;
	std::vector<physx::PxArticulationLink*> links;
	std::vector<physx::PxArticulationJoint*> joints;
	std::vector<physx::PxShape> shapes;
	const physx::PxMaterial* material;

public:
	Articulator(const physx::PxMaterial* mat);
	void Render() override;
	void AddLink(const physx::PxTransform pose, const physx::PxGeometry& geometry, const physx::PxMaterial* material, float mass, float distanceBetweenJoints);
	void Update(float dt) override {};
	virtual physx::PxShape* CreateShape(const physx::PxGeometry& geom, const physx::PxVec3& col) { return nullptr; };
	void AddArticulator();

};

