#include "proch3d.h"

P3d_Camera::P3d_Camera() { //set default values
	persp.fov = 45.f;
	persp.aspect_ratio = DEFAULT_SCREEN_WIDTH / DEFAULT_SCREEN_HEIGHT;
	persp.near = 1.f;
	persp.far = 100.f;

	projectionMatrix = glm::perspective(persp.fov, persp.aspect_ratio, persp.near, persp.far);
}

glm::mat4 P3d_Camera::get_view_matrix() {
	return glm::inverse(modelMatrix);
}

