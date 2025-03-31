#pragma once
#include <PxPhysicsAPI.h>

namespace Renderer {
	void Setup(int x, int y, const char* title);
	void Start();

	void RenderGeometry(const physx::PxGeometryHolder& geometry);

	void RenderSphere(const physx::PxGeometryHolder& geometry);
	void RenderPlane();
}