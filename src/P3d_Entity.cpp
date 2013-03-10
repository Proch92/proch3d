#include "proch3d.h"

P3d_Entity::P3d_Entity() {
};

void P3d_Entity::translate(float x, float y, float z) {
	position.x += x;
	position.y += y;
	position.z += z;
}

void P3d_Entity::translate(const P3d_Vector3f& movement) {
	position.x += movement.x;
	position.y += movement.y;
	position.z += movement.z;
}

void P3d_Entity::rotate(float A, float B, float C) {
	orientation.x += A;
	if(orientation.x >= 360) orientation.x -= 360;
	if(orientation.x < 0) orientation.x += 360;

	orientation.y += B;
	if(orientation.y >= 360) orientation.y -= 360;
	if(orientation.y < 0) orientation.y += 360;
	
	orientation.z += C;
	if(orientation.z >= 360) orientation.z -= 360;
	if(orientation.z < 0) orientation.z += 360;
}