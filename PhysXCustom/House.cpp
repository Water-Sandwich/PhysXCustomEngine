#include "House.h"
#include "FixedJoint.h"

using namespace physx;

void House::MakeBricks(int wallHeight, int bricksX, int bricksY, const physx::PxVec3& brickSize, const physx::PxTransform& pose, const physx::PxVec3& color, float gap)
{
	auto brickPose = pose;

	//front
	for (int y = 0; y < wallHeight; y++) {
		brickPose.p.x = pose.p.x;
		int temp = 0;
		if (y % 2 == 0) {
			temp++;
			brickPose.p.x += brickSize.x;
		}

		for (int x = 0; x < bricksX + (y % 2); x++) {
			auto brick = new HouseBrick(brickPose, brickSize, color);
			bricks.push_back(brick);
			brickPose.p.x += (brickSize.x * 2) + gap;
		}

		brickPose.p.y += (brickSize.y * 2);
	}

	//side 1
	brickPose = pose;
	PxQuat rot(PxHalfPi, { 0,1,0 });
	brickPose.q = rot * brickPose.q;
	brickPose.p.y = pose.p.y;
	brickPose.p.x = (((brickSize.x * 2) + gap) * bricksX) + brickSize.z;
	brickPose.p.z += gap;

	for (int y = 0; y < wallHeight; y++) {
		brickPose.p.z = pose.p.z + brickSize.z;
		int temp = 0;
		if (y % 2 == 1) {
			temp--;
			brickPose.p.z += brickSize.x;
		}

		for (int x = 0; x < bricksY + temp + 1; x++) {
			auto brick = new HouseBrick(brickPose, brickSize, color);
			bricks.push_back(brick);
			brickPose.p.z += (brickSize.x * 2) + gap;
		}

		brickPose.p.y += (brickSize.y * 2);
	}

	//side 2

	brickPose.p = pose.p;
	brickPose.p.x -= brickSize.z + gap;
	brickPose.p.z += gap;

	for (int y = 0; y < wallHeight; y++) {
		brickPose.p.z = pose.p.z + brickSize.z;
		int temp = 0;
		if (y % 2 == 1) {
			temp--;
			brickPose.p.z += brickSize.x;
		}

		for (int x = 0; x < bricksY + temp + 1; x++) {
			auto brick = new HouseBrick(brickPose, brickSize, color);
			bricks.push_back(brick);
			brickPose.p.z += (brickSize.x * 2) + gap;
		}

		brickPose.p.y += (brickSize.y * 2);
	}

	//back 

	brickPose.p = pose.p;
	brickPose.p.x -= brickSize.z + gap;
	brickPose.p.z += (((brickSize.x * 2) + gap) * bricksY) + (brickSize.z * 2);

	rot = { PxHalfPi, { 0,1,0 } };
	brickPose.q = rot * brickPose.q;

	for (int y = 0; y < wallHeight; y++) {
		brickPose.p.x = pose.p.x;
		int temp = 0;
		if (y % 2 == 0) {
			temp++;
			brickPose.p.x += brickSize.x;
		}

		for (int x = 0; x < bricksX + (y % 2); x++) {
			auto brick = new HouseBrick(brickPose, brickSize, color);
			bricks.push_back(brick);
			brickPose.p.x += (brickSize.x * 2) + gap;
		}

		brickPose.p.y += (brickSize.y * 2);
	}


	for (auto brick : bricks)
		brick->AddThis();
}

void House::MakeBeams(const physx::PxVec3& beamSize, const physx::PxVec3 positions[4])
{
	beams.reserve(4);
	for (int i = 0; i < 4; i++) {
		beams.push_back(new SteelBeam(beamSize, PxTransform(positions[i]), { 0.1,0.1,0.1 }));
	}

	for (auto beam : beams)
		beam->AddThis();
}

House::House(int wallHeight, int bricksX, int bricksY, const physx::PxVec3& brickSize, const physx::PxTransform& pose, const physx::PxVec3& color, float gap)
{
	MakeBricks(wallHeight, bricksX, bricksY, brickSize, pose, color, gap);
	PxVec3 beamSize = { 0.2, wallHeight * brickSize.y, 0.2 };

	float h = (wallHeight * brickSize.y) + (pose.p.y / 2);

	PxVec3 positions[4] = {
		{brickSize.z + (beamSize.x * 2.5f), h, (brickSize.x) + (beamSize.z * 2.5f)},
		{(beamSize.x * 2.5f) + (brickSize.x * bricksX * 2) - brickSize.z, h, (brickSize.x) + (beamSize.z * 2.5f)},
		{brickSize.z + (beamSize.x * 2.5f), h, (beamSize.x * 2.5f) + (brickSize.x * bricksY * 2) - brickSize.z},
		{(beamSize.x * 2.5f) + (brickSize.x * bricksX * 2) - brickSize.z, h, (beamSize.x * 2.5f) + (brickSize.x * bricksY * 2) - brickSize.z}
	};

	MakeBeams(beamSize, positions);
}
