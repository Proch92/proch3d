#include "proch3d.h"

P3d_Camera::P3d_Camera() { //set default values
}

void P3d_Camera::camera_glulookat() {
	glRotatef(-orientation.z, 0.0, 0.0, 1.0); //this happen third
	glRotatef(-orientation.y, 0.0, 1.0, 0.0); //this happen second
	glRotatef(-orientation.x, 1.0, 0.0, 0.0); //this happen first
	glTranslatef(-position.x, -position.y, -position.z);
}
