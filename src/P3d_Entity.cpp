#include "proch3d.h"

P3d_Entity::P3d_Entity() {
	position = glm::vec3(0.0, 0.0, 0.0);
	modelChanged = true;
};

void P3d_Entity::translate(float x, float y, float z) {
	position.x += x;
	position.y += y;
	position.z += z;

	modelChanged = true;
}

void P3d_Entity::translate(const glm::vec3& movement) {
	position += movement;

	modelChanged = true;
}

void P3d_Entity::set_position(glm::vec3 newpos) {
	position = newpos;

	modelChanged = true;
}

void P3d_Entity::rotate(float A, float B, float C) {
	rotation = glm::quat(glm::vec3(A, B, C)) * rotation;

	modelChanged = true;
}

void P3d_Entity::rotate(float angle, glm::vec3 axis) {
	rotation = glm::angleAxis(angle, axis) * rotation;

	modelChanged = true;
}

glm::vec3 P3d_Entity::get_position() {
	return position;
}

glm::vec3 P3d_Entity::get_orientation() {
	return rotation * glm::vec3(0.0, 1.0, 0.0);
}

glm::quat P3d_Entity::get_rotation() {
	return rotation;
}