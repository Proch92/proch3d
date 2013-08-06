#include "proch3d.h"

P3d_Camera::P3d_Camera() { //set default values
	persp.fov = 45.f;
	persp.aspect_ratio = DEFAULT_SCREEN_WIDTH / DEFAULT_SCREEN_HEIGHT;
	persp.near = 1.f;
	persp.far = 100.f;

	projectionMatrix = glm::perspective(persp.fov, persp.aspect_ratio, persp.near, persp.far);

	lookAt = glm::rotate(glm::mat4(), (float)90.0, glm::vec3(-1.0, 0.0, 0.0));
}

//override
void P3d_Camera::update_model_matrix() {
	if(modelChanged) {
		modelMatrix = lookAt * glm::mat4_cast(glm::inverse(rotation)) * glm::translate(glm::mat4(1.0), -position);
		modelChanged = false;
	}
}
