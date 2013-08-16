#include "proch3d.h"

P3d_Camera::P3d_Camera() { //set default values
	persp.fov = 45.f;
	persp.aspect_ratio = DEFAULT_SCREEN_WIDTH / DEFAULT_SCREEN_HEIGHT;
	persp.near = 1.f;
	persp.far = 100.f;

	projectionMatrix = glm::perspective(persp.fov, persp.aspect_ratio, persp.near, persp.far);

	//lookAt = glm::rotate(glm::mat4(), (float)90.0, glm::vec3(-1.0, 0.0, 0.0));
	cameraRotation = glm::vec3(0.0, 0.0, 0.0);
}

void P3d_Camera::yaw(float angle) {
	cameraRotation[0] += angle;

	while(cameraRotation[0] >= 360)
		cameraRotation[0] -= 360;
	while(cameraRotation[0] < 0)
		cameraRotation[0] += 360;

	modelChanged = true;
}

void P3d_Camera::pitch(float angle) {
	cameraRotation[1] += angle;

	if(cameraRotation[1] > 90)
		cameraRotation[1] = 90;
	if(cameraRotation[1] < -90)
		cameraRotation[1] = -90;

	modelChanged = true;
}

//override
//movement [front, side, up]
void P3d_Camera::orientedMove(glm::vec3 movement) {
	/*glm::vec3 front = rotation * FRONT;
	glm::vec3 up = rotation * UP;
	glm::vec3 right = rotation * RIGHT;*/
	//glm::mat4 transMat = glm::rotate(glm::mat4(), -cameraRotation[1], glm::vec3(1.0, 0.0, 0.0)) * glm::rotate(glm::mat4(), -cameraRotation[0], glm::vec3(0.0, 0.0, 1.0));
	//glm::vec3 front(cos(cameraRotation[0] * DEG2RAD)*cos(cameraRotation[1] * DEG2RAD), cos(cameraRotation[0] * DEG2RAD)*sin(cameraRotation[1] * DEG2RAD), sin(cameraRotation[0] * DEG2RAD));
	
	glm::vec3 unit_vector(cos(cameraRotation[0] * DEG2RAD) * cos(cameraRotation[1] * DEG2RAD), sin(cameraRotation[0] * DEG2RAD) * cos(cameraRotation[1] * DEG2RAD), sin(cameraRotation[1] * DEG2RAD));
	//printf("cameraRotation: "); print_vec3(cameraRotation);
	//printf("unit_vector: "); print_vec3(unit_vector);
	glm::vec3 world_vector(-unit_vector.y, unit_vector.x, unit_vector.z);
	//printf("world_vector: "); print_vec3(world_vector);
	glm::vec3 right(-sin((cameraRotation[0] - 90) * DEG2RAD), cos((cameraRotation[0] - 90) * DEG2RAD), 0.0);
	//printf("right: "); print_vec3(right);
	
	//moving forward
	position.x += movement.x * world_vector.x;
	position.y += movement.x * world_vector.y;
	position.z += movement.x * world_vector.z;

	//moving side
	position.x += movement.y * right.x;
	position.y += movement.y * right.y;
	position.z += 0;
	
	//position += glm::vec3(front.x * movement.x, front.y * movement.x, front.z * movement.x);
	//position += glm::vec3(right.x * movement.y, right.y * movement.y, right.z * movement.y);
	//position += glm::vec3(up.x * movement.z, up.y * movement.z, up.z * movement.z);

	modelChanged = true;
}

//override
void P3d_Camera::update_model_matrix() {
	if(modelChanged) {
		//with quaternions ----------------------------------------------------------------------------------------
		//adjust up direction;
		/*glm::vec3 direction = rotation * glm::vec3(0.0, 1.0, 0.0);
		printf("direction: "); print_vec3(direction);
		glm::vec3 right = glm::cross(direction, glm::vec3(0.0, 0.0, 1.0));
		printf("right: "); print_vec3(right);
		glm::vec3 desiredUp = glm::cross(right, direction);
		printf("desiredUp: "); print_vec3(desiredUp);
		glm::vec3 newUp = rotation * glm::vec3(0.0, 0.0, 0.1);
		printf("newUp: "); print_vec3(newUp);
		rotation = RotationBetweenVectors(newUp, desiredUp) * rotation;

		modelMatrix = glm::mat4_cast(glm::inverse(rotation)) * glm::translate(glm::mat4(1.0), -position);*/
		//print_vec3(rotation * FRONT);
		//glm::mat4 rotationMatrix = glm::rotate(glm::mat4(), -glm::pitch(rotation), glm::vec3(1.0, 0.0, 0.0));
		//rotationMatrix = glm::rotate(rotationMatrix, -glm::yaw(rotation), glm::vec3(0.0, 0.0, 1.0));

		//glm::vec3 angles = glm::eulerAngles(rotation);
		//modelMatrix = glm::rotate(glm::mat4(), -angles.y, glm::vec3(0.0, 1.0, 0.0)) * glm::rotate(glm::mat4(), -angles.x, glm::vec3(1.0, 0.0, 0.0)) * glm::translate(glm::mat4(), -position);
		//modelMatrix = rotationMatrix * glm::translate(glm::mat4(), -position);
		//modelMatrix = glm::mat4_cast(glm::inverse(rotation)) * glm::translate(glm::mat4(), -position);
		//modelMatrix = glm::lookAt(position, rotation * FRONT, UP);

		//print_mat4(modelMatrix);
		//---------------------------------------------------------------------------------------------------------

		//with vec3 [yaw, pitch, roll] ----------------------------------------------------------------------------
		//glm::mat4 rotationMatrix = glm::rotate(glm::mat4(), -cameraRotation[1], glm::vec3(1.0, 0.0, 0.0));
		//rotationMatrix = glm::rotate(rotationMatrix, -cameraRotation[0], glm::vec3(0.0, 0.0, 1.0));
		
		modelMatrix = glm::rotate(glm::mat4(), -cameraRotation[1] - 90, glm::vec3(1.0, 0.0, 0.0)) * glm::rotate(glm::mat4(), -cameraRotation[0], glm::vec3(0.0, 0.0, 1.0)) * glm::translate(glm::mat4(1.0), -position);
		//---------------------------------------------------------------------------------------------------------

		modelChanged = false;
	}
}