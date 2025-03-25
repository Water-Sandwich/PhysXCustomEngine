#pragma once
#include "GameObject.h"
#include "PxPhysicsAPI.h"
#include <string>
#include <vector>

class PxGameObject : public GameObject
{
protected:
	std::vector<physx::PxShape*> shapes;

	virtual physx::PxShape* CreateShape(const physx::PxGeometry& geom) = 0;
	void SetMaterial(std::string name);
	physx::PxRigidActor* GetRigid();
	void InitShapes();
	physx::PxTransform GetPose(physx::PxShape* shape);
	physx::PxMat44 GetMatrix(const physx::PxTransform& transform);
	float* GetGLMatrix(const physx::PxTransform& transform);

public:
	physx::PxActor* actor;
	physx::PxMaterial* material;

	PxGameObject();
	~PxGameObject();
};