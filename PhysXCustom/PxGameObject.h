#pragma once
#include "GameObject.h"
#include "PxPhysicsAPI.h"
#include <string>
#include <vector>

enum class Layer : int
{
	TestA	= (1 << 0),
	TestB	= (1 << 1),
	TestC	= (1 << 2)
};


class PxGameObject : public GameObject
{
protected:
	std::vector<physx::PxShape*> shapes;

	virtual physx::PxShape* CreateShape(const physx::PxGeometry& geom, const physx::PxVec3& col) = 0;
	void SetMaterial(std::string name);
	physx::PxRigidActor* GetRigid();
	void InitShapes();
	physx::PxTransform GetPose(physx::PxShape* shape);
	physx::PxMat44 GetMatrix(const physx::PxTransform& transform);
	float* GetGLMatrix(const physx::PxTransform& transform);

public:
	physx::PxActor* actor;
	const physx::PxMaterial* material;

	PxGameObject();
	~PxGameObject();

	void RenderShapes();
	void RenderShape(physx::PxShape* shape);
	void RenderShape(physx::PxShape* shape, const physx::PxTransform& pose, const physx::PxVec3& color);

	void SetTrigger(bool isTrigger);
	void SetFilters(Layer filterGroup, Layer filterMask);
};