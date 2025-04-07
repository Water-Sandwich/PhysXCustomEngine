#pragma once
#include <PxPhysicsAPI.h>

namespace Renderer {
	void Setup(int x, int y, const char* title);
	void Start();

	void RenderGeometry(physx::PxShape* const shape);

	void RenderSphere(const physx::PxGeometryHolder& geometry);
	void RenderPlane(physx::PxShape* const shape);
	void RenderCapsule(const physx::PxGeometryHolder& geometry);
}