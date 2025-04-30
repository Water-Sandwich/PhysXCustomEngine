#include "Articulator.h"
#include "PhysicsEngine.h"

using namespace physx;

Articulator::Articulator(const physx::PxGeometry& geometry, const physx::PxMaterial* mat, const physx::PxVec3& _color) : PxGameObject()
{
	articulator = PhysicsEngine::createArticulation();
	articulator->setStabilizationThreshold(0);
	articulator->setMaxProjectionIterations(16);
	articulator->setSeparationTolerance(0.001f);
	material = mat;
	shape = PhysicsEngine::createShape(geometry, material);
	color = _color;
}

void Articulator::Render()
{
	for (auto l : links) {
		auto pose = l->getGlobalPose();

		RenderShape(shape, pose, color);
	}
}

void Articulator::AddLink(const physx::PxTransform& pose, float mass, float distanceBetweenJoints)
{
	PxArticulationLink* link;
	if(links.size() == 0)
		link = articulator->createLink(NULL, pose);
	else
		link = articulator->createLink(links.back(), pose);

	links.push_back(link);
	link->attachShape(*shape);
	PxRigidBodyExt::setMassAndUpdateInertia(*link, mass);

	PxArticulationJoint* joint = link->getInboundJoint();
	if (joint) {
		joint->setParentPose(PxTransform(0, distanceBetweenJoints, 0));
		joint->setChildPose(PxTransform(0, -distanceBetweenJoints, 0));
		joints.push_back(joint);
	}

	PhysicsEngine::AddActor(link);
}

void Articulator::AddLinks(physx::PxTransform startPose, const physx::PxVec3& direction, float mass, int numLinks)
{
	float dist = direction.magnitude();
	for (int i = 0; i < numLinks; i++) {
		AddLink(startPose, mass, dist / 2);
		startPose.p += direction;
	}
}

void Articulator::AddArticulator()
{
	PhysicsEngine::addArticulation(articulator);
}

physx::PxArticulationLink* Articulator::getFirstLink()
{
	if (links.size() == 0)
		return nullptr;

	return links.front();
}

physx::PxArticulationLink* Articulator::getLastLink()
{
	if (links.size() == 0)
		return nullptr;

	return links.back();
}