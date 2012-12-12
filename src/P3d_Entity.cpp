#include "proch3d.h"

P3d_Entity::P3d_Entity() {
	orient = P3d_Vector4f(0.0, 0.0, 1.0, 1.0);
};

void P3d_Entity::translate(float x, float y, float z) {
	position.x += x;
	position.y += y;
	position.z += z;
}

void P3d_Entity::rotate(float A, float B, float C) {
	if(orient[2] < 0) A = -A;
	
	if(orientation.x + A >= 180)
		A = 180 - orientation.x;
	/*if(orientation.x + A <= -180)
		A = -180 - orientation.x;*/
	orientation.x += A;
	
	orientation.y += B;
	if(orientation.y >= 360) orientation.y -= 360;
	if(orientation.y < 0) orientation.y += 360;
	
	orientation.z += C;
	if(orientation.z >= 360) orientation.z -= 360;
	if(orientation.z < 0) orientation.z += 360;
	
	glPushMatrix();
	glLoadIdentity();
	glRotatef(C, 0.0, 0.0, 1.0);
	glRotatef(B, 0.0, 1.0, 0.0);
	glRotatef(A, 1.0, 0.0, 0.0);
	
	/*glBegin(GL_POINT);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(orient[0] * 50, orient[1] * 50, orient[2] * 50);
	glEnd();*/
	
	P3d_Matrix4f matrix;
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix.get_data());
	//matrix.show();
	orient = matrix * orient;
	
	glPopMatrix();
	
	//printf("orient: %f, %f, %f\n", orient[0], orient[1], orient[2]);
}

void P3d_Entity::moveOriented(const P3d_Vector3f& movement) {
	//position += orient * movement;
	
	//z movement
	position.x += orient[0] * movement.z;
	position.y += orient[1] * movement.z;
	position.z += orient[2] * movement.z * (-1);
	//x movement
	position.x += (1 - orient[0]) * movement.x;
	position.z += (1 - orient[2]) * movement.x;
}

void P3d_Entity::move(const P3d_Vector3f& movement) {
	//position += orient * movement;
	
	//z movement
	position.x += movement.x;
	position.y += movement.y;
	position.z += movement.z;
}

P3d_Vector4f& P3d_Entity::get_orient() {
	return orient;
}
