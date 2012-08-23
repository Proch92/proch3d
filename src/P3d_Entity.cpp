#include "proch3d.h"

P3d_Entity::P3d_Entity() {
};

void P3d_Entity::translate(float x, float y, float z) {
	position.x += x;
	position.y += y;
	position.z += z;
}

void P3d_Entity::rotate(float A, float B, float C) {
	orientation.x += A;
	orientation.y += B;
	orientation.z += C;
}

