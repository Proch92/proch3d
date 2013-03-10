#include "proch3d.h"

P3d_Object::P3d_Object() {
	hidden = false;
}

void P3d_Object::render() {
	if(hidden) return;
	
	glPushMatrix();
	
	glTranslatef(position.x, position.y, position.z);
	glRotatef(orientation.z, 0.0, 0.0, 1.0); //this happen third
	glRotatef(orientation.y, 0.0, 1.0, 0.0); //this happen second
	glRotatef(orientation.x, 1.0, 0.0, 0.0); //this happen first
	
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINE_LOOP);
		glVertex3f(-2.5, -2.5, 0);
		glVertex3f(-2.5, 2.5, 0);
		glVertex3f(2.5, 2.5, 0);
		glVertex3f(2.5, -2.5, 0);
	glEnd();
	
	glPopMatrix();
}

void P3d_Object::set_color(const P3d_Color4f& new_color) {
	color = new_color;
}
