#include "proch3d.h"

P3d_Camera::P3d_Camera() { //set default values
	set_frustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0); //default frustum
}

void P3d_Camera::camera_glulookat() {
	glRotatef(-orientation.z, 0.0, 0.0, 1.0); //this happen third
	glRotatef(-orientation.y, 0.0, 1.0, 0.0); //this happen second
	glRotatef(-orientation.x, 1.0, 0.0, 0.0); //this happen first
	glTranslatef(-position.x, -position.y, -position.z);
}

void P3d_Camera::set_frustum(struct P3d_frustum f) {
	frustum = f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(frustum.left, frustum.right, frustum.bottom, frustum.top, frustum.near, frustum.far);
	glMatrixMode(GL_MODELVIEW);
}

void P3d_Camera::set_frustum(int l, int r, int b, int t, int n, int f) {
	frustum.left = l;
	frustum.right = r;
	frustum.bottom = b;
	frustum.top = t;
	frustum.near = n;
	frustum.far = f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(frustum.left, frustum.right, frustum.bottom, frustum.top, frustum.near, frustum.far);
	glMatrixMode(GL_MODELVIEW);
}

struct P3d_frustum* P3d_Camera::get_frustum() {
	return &frustum;
}