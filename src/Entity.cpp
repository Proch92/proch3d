#include "proch3d.h"

Entity::Entity() {
};

void Entity::translate(float x, float y, float z) {
	position.x += x;
	position.y += y;
	position.z += z;
}

void Entity::rotate(float A, float B, float C) {
	orientation.x += A;
	orientation.y += B;
	orientation.z += C;
}

