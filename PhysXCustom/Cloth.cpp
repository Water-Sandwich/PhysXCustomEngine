#include "Cloth.h"
#include "PhysicsEngine.h"
#include "Renderer.h"

using namespace physx;

Cloth::Cloth(const physx::PxTransform& pose, const physx::PxVec2& size, const physx::PxVec2& subDivisions, const physx::PxVec3& colour) : PxGameObject()
{
	particles.reserve((subDivisions.x + 1) * (subDivisions.y + 1));
	quads.resize(subDivisions.x * subDivisions.y);

	const PxVec2 stride(size.x / subDivisions.x, size.y / subDivisions.y);

	//make particles
	for (int x = 0; x < subDivisions.x + 1; x++) {
		for (int y = 0; y < subDivisions.y + 1; y++) {
			PxClothParticle particle({ stride.x * x, 0, stride.y * y }, 1);
			particles.push_back(particle);
		}
	}

	//connect particles to make quads
	for (int x = 0; x < subDivisions.x; x++) {
		for (int y = 0; y < subDivisions.y; y++) {
			int i = (y * subDivisions.y) + x;
			Vec4I quad = {
				(y) * (subDivisions.x + 1) + x,
				(y) * (subDivisions.x + 1) + (x + 1),
				(y + 1) * (subDivisions.x + 1) + (x + 1),
				(y + 1) * (subDivisions.x + 1) + x
			};
			quads[i] = (quad);
		}
	}

	mesh.points.data = &particles[0];
	mesh.points.count = particles.size();
	mesh.points.stride = sizeof(PxClothParticle);

	mesh.invMasses.data = &(particles[0].invWeight);
	mesh.invMasses.count = particles.size();
	mesh.invMasses.stride = sizeof(PxClothParticle);

	mesh.quads.data = &quads[0];
	mesh.quads.count = quads.size();
	mesh.quads.stride = sizeof(Vec4I);

	//fabric
	fabric = PhysicsEngine::createClothFabric(&mesh);
	actor = PhysicsEngine::createCloth(pose, fabric, particles, PxClothFlag::eSCENE_COLLISION);
	PhysicsEngine::AddActor(actor);

	color = { colour };
}

void Cloth::Render()
{
	Renderer::RenderCloth(*this);
}

const std::vector<physx::PxClothParticle>* Cloth::getParticles() const
{
	return &particles;
}

const std::vector<Vec4I>* Cloth::getQuads() const
{
	return &quads;
}

physx::PxVec3* Cloth::getColor() const
{
	return const_cast<PxVec3*>(&color);
}

const physx::PxClothMeshDesc* Cloth::getMesh() const
{
	return &mesh;
}