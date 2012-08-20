#include "proch3d.h"

Entity::Entity() {
};

void Entity::translate(float x, float y, float z) {
	matrix[12] += x;
	matrix[13] += y;
	matrix[14] += z;
	
	//------------
	
	position.x += x;
	position.y += y;
	position.z += z;
}

void Entity::rotate(float A, float B, float C) {
	glPushMatrix();
	
	glLoadMatrixf(matrix.get_data());
	
	glRotatef(C, 0.0, 0.0, 1.0);
	glRotatef(B, 0.0, 1.0, 0.0);
	glRotatef(A, 1.0, 0.0, 0.0);
	
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix.get_data());
	
	glPopMatrix();
	
	//-----------
	
	orientation.x += A;
	orientation.y += B;
	orientation.z += C;
}

