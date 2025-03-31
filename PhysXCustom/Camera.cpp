#include "Camera.h"

using namespace physx;

physx::PxVec3 inputdir{ 0,0,0 };

Camera::Camera() {
	pos = { 0, 5, 15 };
	dir = { 1, 0, 0, };
}
void Camera::Update(float dt)
{	
	PxVec3 forward = dir.getNormalized();
	PxVec3 right = forward.cross(PxVec3(0, 1, 0)).getNormalized();
	PxVec3 up = right.cross(forward).getNormalized(); // Get a local axis based on the direction the camera is facing.

	PxVec3 movement = inputdir.getNormalized();
	movement = (forward * movement.x) + (up * movement.y) + (right * movement.z); // Multiply movement by local axis to make it relative to camera direction.

	pos += movement * dt * speed;
}

//EWWWWW TODO: FIX THIS UGLY MESS YUCK
void Camera::onKeyDown(unsigned char c)
{
	switch (toupper(c))
	{
	case 'W':
		inputdir.x += 1;
		break;

	case 'S':
		inputdir.x -= 1;
		break;

	case 'A':
		inputdir.z -= 1;
		break;

	case 'D':
		inputdir.z += 1;
		break;

	case 'Z':
		inputdir.y -= 1;
		break;
		
	case 'X':
		inputdir.y += 1;
		break;
	}
}

void Camera::onKeyUp(unsigned char c)
{
	switch (toupper(c))
	{
	case 'W':
		inputdir.x -= 1;
		break;

	case 'S':
		inputdir.x += 1;
		break;

	case 'A':
		inputdir.z += 1;
		break;

	case 'D':
		inputdir.z -= 1;
		break;

	case 'Z':
		inputdir.y += 1;
		break;

	case 'X':
		inputdir.y -= 1;
		break;
	}
}

void Camera::onMouseEvent(int x, int y)
{
	PxVec3 viewY = dir.cross(PxVec3(0, 1, 0)).getNormalized();

	PxQuat qx(PxPi * x * sensitivity / 180.0f, PxVec3(0, 1, 0));
	dir = qx.rotate(dir);

	PxQuat qy(PxPi * y * sensitivity / 180.0f, viewY);
	dir = qy.rotate(dir);

	dir.normalize();
}