#include "src/proch3d.h"

Water::Water(int x, int y) {
	dimx = x;
	dimy = y;
	
	P = DEFAULT_P;
	I = DEFAULT_I;
	D = DEFAULT_D;
	
	matrix = (Node**) malloc(sizeof(Node*) * dimx);
	int i;
	for(i=0; i!=dimx; i++) {
		matrix[i] = new Node[dimy];
		int j;
		for(j=0; j!=dimy; j++) {
			matrix[i][j].yval = 0;
			matrix[i][j].setPID(P, I, D);
		}
	}
	
	color.r = 0;
	color.g = 0;
	color.b = 1;
	color.a = 0.5;
}

void Water::setPID(float p, float i, float d) {
	P = p;
	I = i;
	D = d;
}

void Water::compute() {
	int i, j;
	
	for(j=0; j!=dimy-1; j++) {
		for(i=0; i!=dimx-1; i++) {
			matrix[i][j] * matrix[i+1][j];
			matrix[i][j] * matrix[i][j+1];
		}
	}
	
	for(j=1; j!=dimy-1; j++)
		for(i=1; i!=dimx-1; i++)
			matrix[i][j].heightCorrection();
	
	for(j=1; j!=dimy - 1; j++)
		for(i=1; i!=dimx - 1; i++)
			matrix[i][j].applyDelta();
}

void Water::show() {
	int i, j;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(color.r, color.g, color.b);
	for(i=1; i!=dimy; i++) {
		glBegin(GL_QUAD_STRIP);
		for(j=0; j!=dimx; j++) {
			glVertex3f(j*SPARE, matrix[j][i].yval, i*SPARE);
			glVertex3f(j*SPARE, matrix[j][i-1].yval, (i-1)*SPARE);
		}
		glEnd();
	}
}

void Water::giveInput(int x, int y, float input) {
	matrix[x][y].vel += input;
}


//Node

Node::Node() {
	yval = 0;
	delta = 0;
	vel = 0;
}

void Node::operator * (Node &node) {
	float diffH;
	float diffV;
	
	diffH = (yval - node.yval) * P;
	delta += diffH;
	node.delta -= diffH;
	
	diffV = (vel - node.vel) * D;
	delta += diffV;
	node.delta -= diffV;
}

void Node::applyDelta() {
	vel -= delta * K;
	yval += vel;
	delta = 0;
}

void Node::heightCorrection() {
	delta += yval * I;
}

void Node::setPID(float p, float i, float d) {
	P = p;
	I = i;
	D = d;
}
