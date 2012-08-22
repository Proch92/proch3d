#include "proch3d.h"

Object::Object() {
	hidden = false;
}

void Object::render() {
	if(hidden) return;
	
	glPushMatrix();
	
	glTranslatef(position.x, position.y, position.z);
	glRotatef(orientation.z, 0.0, 0.0, 1.0); //this happen third
	glRotatef(orientation.y, 0.0, 1.0, 0.0); //this happen second
	glRotatef(orientation.x, 1.0, 0.0, 0.0); //this happen first
	
	glColor3f(color.r, color.g, color.b);
	glutWireCube(5.0); // Box.
	
	glPopMatrix();
}
