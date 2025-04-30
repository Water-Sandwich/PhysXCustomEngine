#pragma once
#include <PxPhysicsAPI.h>
#include "Cloth.h"

namespace Renderer {
	void Setup(int x, int y, const char* title);
	void Start();

	void RenderGeometry(physx::PxShape* const shape);
	void RenderGeometry(physx::PxShape* const shape, const physx::PxVec3& color);
	void SwitchGeometry(const physx::PxGeometryHolder& geometry);

	void RenderSphere(const physx::PxGeometryHolder& geometry);
	void RenderPlane(physx::PxShape* const shape);
	void RenderCapsule(const physx::PxGeometryHolder& geometry);
	void RenderBox(const physx::PxGeometryHolder& geometry);
	void RenderConvexMesh(const physx::PxGeometryHolder& geometry);
	void RenderTriangleMesh(const physx::PxGeometryHolder& geometry);
	void RenderCloth(const Cloth& cloth);
}