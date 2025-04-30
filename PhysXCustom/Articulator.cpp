#include "Articulator.h"
#include "PhysicsEngine.h"

using namespace physx;

Articulator::Articulator(const physx::PxMaterial* mat) : PxGameObject()
{
	articulator = PhysicsEngine::createArticulation();
	articulator->setStabilizationThreshold(0);
	articulator->setMaxProjectionIterations(16);
	articulator->setSeparationTolerance(0.001f);
	material = mat;
}

void Articulator::Render()
{
}

void Articulator::AddLink(const physx::PxTransform pose, const physx::PxGeometry& geometry, const physx::PxMaterial* material, float mass, float distanceBetweenJoints)
{
	//PxArticulationLink* link;
	//if(links.size() == 0)
	//	link = articulator->createLink(NULL, pose);
	//else
	//	link = articulator->createLink(*links.end(), pose);

	//auto shape = CreateShape(geometry, { 1,1,1 });
	//link->attachShape(*shape);
	//PxRigidBodyExt::setMassAndUpdateInertia(*link, mass);

	//PxArticulationJoint* joint = link->getInboundJoint();
	//if (joint) {
	//	joint->setParentPose(PxTransform(0, distanceBetweenJoints, 0));
	//	joint->setChildPose(PxTransform(0, -distanceBetweenJoints, 0));
	//	joints.push_back(joint);
	//}

	//PhysicsEngine::AddActor(link);
}

void Articulator::AddArticulator()
{
	PhysicsEngine::addArticulation(articulator);
}
