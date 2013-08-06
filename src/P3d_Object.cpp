#include "proch3d.h"

P3d_Object::P3d_Object() {
	hidden = false;
	mesh = NULL;
	
	vertices = NULL;
	texcoords = NULL;
	colors = NULL;

	num_vertices = 0;
	num_indices = 0;	
}

void P3d_Object::render(glm::mat4 &proj) {
	if(hidden) return;

	if(modelChanged) {
		modelMatrix = glm::translate(glm::mat4(1.0), position) * glm::mat4_cast(rotation);

		modelChanged = false;
	}
	
	GLint uniProj = glGetUniformLocation(shader_program, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	/*GLint uniView = glGetUniformLocation(shader_program, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));*/

	GLint uniModel = glGetUniformLocation(shader_program, "model");
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);

	if(mesh != NULL)
		mesh->render();
}

void P3d_Object::set_mesh(P3d_Mesh* m) {
	mesh = m;
}

void P3d_Object::set_shader_program(GLuint sp) {
	shader_program = sp;

	glBindBuffer(GL_ARRAY_BUFFER, vb);
	GLint posAttrib = glGetAttribLocation(shader_program, "inPosition");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, cb);
	GLint colAttrib = glGetAttribLocation(shader_program, "inColor");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void P3d_Object::load_cube(int n) {
	num_vertices = 8;
	float n2 = (float)n / 2;
	vertices = new float[24] {
		-n2, -n2, -n2,
		n2, -n2, -n2,
		n2, -n2, n2,
		-n2, -n2, n2,

		-n2, n2, -n2,
		n2, n2, -n2,
		n2, n2, n2,
		-n2, n2, n2
	};

	texcoords = new float[72] {
		0.0, 0.0,
		0.0, 1.0,
		1.0, 1.0,
		1.0, 1.0,
		1.0, 0.0,
		0.0, 0.0
	};
	int i;
	for(i=2; i!=7; i++)
		memcpy(&(texcoords[i*12]), texcoords, 12*sizeof(float));

	indices = new int[36] {
		0,1,2,
		2,3,0,

		4,5,6,
		6,7,4,

		3,7,6,
		6,2,3,

		0,4,7,
		7,3,0,

		1,5,4,
		4,0,1,

		2,6,5,
		5,1,2
	};
	num_indices = 36;

	colors = new float[32] {
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,

		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0
	};

	//creating gpu memory buffers
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, num_vertices * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * 2 * sizeof(int), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &cb);
	glBindBuffer(GL_ARRAY_BUFFER, cb);
	glBufferData(GL_ARRAY_BUFFER, num_vertices * 4 * sizeof(float), colors, GL_STATIC_DRAW);
}

void P3d_Object::load_tetrahedron() {
	num_vertices = 4;
	vertices = new float[12] {
		0, 0, 0,
		0.5, sqrtf(3)/2, 0,
		1.0, 0.0, 0.0,
		0.5, 1.0/3.0, sqrtf(2.0/3.0)
	};

	texcoords = new float[24] {
		0, 0,
		0.5, sqrtf(3)/2,
		1.0, 0.0
	};
	int i;
	for(i=2; i!=5; i++)
		memcpy(&(texcoords[i*6]), texcoords, 6*sizeof(float));

	indices = new int[12] {
		0, 2, 1,
		0, 3, 2,
		2, 3, 1,
		1, 3, 0
	};
	num_indices = 12;

	colors = new float[16] {
		1.0, 0.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		1.0, 0.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0
	};

	//creating gpu memory buffers
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, num_vertices * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * 2 * sizeof(int), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &cb);
	glBindBuffer(GL_ARRAY_BUFFER, cb);
	glBufferData(GL_ARRAY_BUFFER, num_vertices * 4 * sizeof(float), colors, GL_STATIC_DRAW);
}

void P3d_Object::load_test() {
}