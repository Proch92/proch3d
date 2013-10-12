#include "proch3d.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

P3d_Mesh::P3d_Mesh() {
	num_object = 0;
	objects = NULL;
}

P3d_Mesh::~P3d_Mesh() {
	delete(objects);
}

bool P3d_Mesh::load_mesh(FILE* fin) {
	fread(&num_object, sizeof(int), 1, fin);
	printf("num_object : %d\n", num_object);

	objects = new Object[num_object];

	for(int i=0; i!=num_object; i++)
		if(objects[i].load(fin) == false) {
			delete(objects);

			return false;
		}

	return true;
}

void P3d_Mesh::render(GLuint shader_program) {
	for(int i=0; i!=num_object; i++)
		objects[i].render(shader_program);
}

P3d_Mesh::Object::Object() {
	vertices = NULL;
	colors = NULL;
	texcoords = NULL;
	normals = NULL;
	indices = NULL;

	material.ambient = 0.6;
	material.diffuse = 0.6;
	material.specular = 0.4;
	material.color = glm::vec4(0.9, 0.3, 0.3, 1.0);

	shading = SMOOTH;
}

P3d_Mesh::Object::~Object() {
	if(vertices != NULL) free(vertices);
	if(colors != NULL) free(colors);
	if(texcoords != NULL) free(texcoords);
	if(normals != NULL) free(normals);
	if(indices != NULL) free(indices);
}

void P3d_Mesh::Object::render(GLuint shader_program) {
	GLuint uniMaterialAmb = glGetUniformLocation(shader_program, "materialAmbient");
	GLuint uniMaterialDif = glGetUniformLocation(shader_program, "materialDiffuse");
	GLuint uniMaterialSpe = glGetUniformLocation(shader_program, "materialSpecular");
	GLuint uniMaterialCol = glGetUniformLocation(shader_program, "materialColor");
	glUniform1f(uniMaterialAmb, material.ambient);
	glUniform1f(uniMaterialDif, material.diffuse);
	glUniform1f(uniMaterialSpe, material.specular);
	glUniform4f(uniMaterialCol, material.color[0], material.color[1], material.color[2], material.color[3]);

	glBindBuffer(GL_ARRAY_BUFFER, vb);
	GLint posAttrib = glGetAttribLocation(shader_program, "inPosition");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	if(shading == SMOOTH) glBindBuffer(GL_ARRAY_BUFFER, nb);
	else glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, nb);
	GLint normAttrib = glGetAttribLocation(shader_program, "inNormal");
	glEnableVertexAttribArray(normAttrib);
	glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
}

bool P3d_Mesh::Object::load(FILE* fin) {
	printf("trace object load\n");
	fread(&num_vertices, sizeof(int), 1, fin);
	fread(&num_faces, sizeof(int), 1, fin);
	printf("num_faces:%d\n", num_indices);
	num_indices = num_faces * 3;
	printf("num_indices:%d\n", num_indices);
	
	//vertex attributes
	vertices = (float*) malloc(sizeof(float) * num_vertices * 3);
	fread(vertices, sizeof(float), num_vertices * 3, fin);

	normals = (float*) malloc(sizeof(float) * num_vertices * 3);
	fread(normals, sizeof(float), num_vertices * 3, fin);

	texcoords = (float*) malloc(sizeof(float) * num_vertices * 2);
	fread(texcoords, sizeof(float), num_vertices * 2, fin);

	//face attributes
	indices = (int*) malloc(sizeof(int) * num_indices);
	fread(indices, sizeof(int), num_indices, fin);

	float *fn = (float*) malloc(sizeof(float) * num_faces * 3);
	fread(fn, sizeof(float), num_faces * 3, fin);
	fnormals = (float*) malloc(sizeof(float) * num_vertices * 3);
	int i;
	for(i=0; i!=num_faces; i++) {
		float* ptr_fn = &(fn[i * 3]);
		memcpy(&fnormals[indices[i*3 + 0] * 3], ptr_fn, sizeof(float) * 3);
		memcpy(&fnormals[indices[i*3 + 1] * 3], ptr_fn, sizeof(float) * 3);
		memcpy(&fnormals[indices[i*3 + 2] * 3], ptr_fn, sizeof(float) * 3);
	}
	free(fn);

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, num_vertices * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof(int), indices, GL_STATIC_DRAW);

	if(shading == FLAT) {
		//flat shading
		glGenBuffers(1, &nb);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, nb);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * 3 * sizeof(float), fnormals, GL_STATIC_DRAW);
	}
	else {
		//smooth shading
		glGenBuffers(1, &nb);
		glBindBuffer(GL_ARRAY_BUFFER, nb);
		glBufferData(GL_ARRAY_BUFFER, num_vertices * 3 * sizeof(float), normals, GL_STATIC_DRAW);
	}

	return true;
}

//load call
P3d_Mesh *P3d_load_mesh(char* filename){
	FILE *fin = fopen(filename, "r");
	if(fin == NULL) {
		printf("error while opening %s\n",filename);
		return NULL;
	}

	P3d_Mesh *newmesh = new P3d_Mesh();

	if(newmesh->load_mesh(fin) == false) {
		free(newmesh);
		newmesh = NULL;
		printf("failed loading mesh\n");
	}

	return newmesh;
}