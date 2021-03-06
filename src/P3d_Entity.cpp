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
	//rotation = glm::rotate(rotation, angle, axis);

	modelChanged = true;
}

//movement [front, side, up]
void P3d_Entity::orientedMove(glm::vec3 movement) {
	glm::vec3 front = rotation * FRONT;
	glm::vec3 up = rotation * UP;
	glm::vec3 right = rotation * RIGHT;
	
	position += glm::vec3(front.x * movement.x, front.y * movement.x, front.z * movement.x);
	position += glm::vec3(right.x * movement.y, right.y * movement.y, right.z * movement.y);
	position += glm::vec3(up.x * movement.z, up.y * movement.z, up.z * movement.z);

	modelChanged = true;
}

void P3d_Entity::update_model_matrix() {
	if(modelChanged) {
		modelMatrix = glm::translate(glm::mat4(1.0), position) * glm::mat4_cast(rotation);

		modelChanged = false;
	}
}

glm::vec3 P3d_Entity::get_position() {
	return position;
}

glm::vec3 P3d_Entity::get_orientation() {
	return rotation * FRONT;
}

glm::quat P3d_Entity::get_rotation() {
	return rotation;
}