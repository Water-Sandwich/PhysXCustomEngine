#include "Camera.h"
#include "Vector2.h"

using namespace physx;

physx::PxVec3 inputdir{ 0,0,0 };

Camera::Camera() {
	pos = { 0, 5, 15 };
	dir = { 0, 1, 0, };
}
void Camera::Update(float dt)
{
	pos += inputdir.getNormalized() * dt * speed;
}

//EWWWWW TODO: FIX THIS UGLY MESS YUCK
void Camera::onKeyDown(unsigned char c)
{
	c = toupper(c);

	//x
	if (c == 'W')
		inputdir.x += 1;
	if (c == 'S')
		inputdir.x -= 1;

	//z
	if (c == 'A')
		inputdir.z -= 1;
	if (c == 'D')
		inputdir.z += 1;

	//y
	if (c == 'Z')
		inputdir.y -= 1;
	if (c == 'X')
		inputdir.y += 1;

}

void Camera::onKeyUp(unsigned char c)
{
	c = toupper(c);

	//x
	if (c == 'W')
		inputdir.x -= 1;
	if (c == 'S')
		inputdir.x += 1;

	//z
	if (c == 'A')
		inputdir.z += 1;
	if (c == 'D')
		inputdir.z -= 1;

	//y
	if (c == 'Z')
		inputdir.y += 1;
	if (c == 'X')
		inputdir.y -= 1;
}

void Camera::onMouseEvent(int x, int y)
{
	//printf("%i, %i\n", x, y);

	//PxVec3 viewY = dir.cross(PxVec3(0, 1, 0)).getNormalized(); //returns {0,0,0}?????
	PxVec3 viewY = { 1,0,0 };

	PxQuat qx(PxPi * x * sensitivity / 180.0f, PxVec3(0, 1, 0));
	dir = qx.rotate(dir);
	PxQuat qy(PxPi * y * sensitivity / 180.0f, viewY);
	dir = qy.rotate(dir);

	dir.normalize();
}
