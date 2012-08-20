#include "proch3d.h"

Object::Object() {
	hidden = false;
}

void Object::render() {
	if(hidden) return;
	
	glMultMatrixf(matrix.get_data());
	
	glColor3f(1.0, 0.0, 0.0);
	glutWireCube(5.0); // Box.
}
