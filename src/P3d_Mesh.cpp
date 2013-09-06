#include "proch3d.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

P3d_Mesh::P3d_Mesh() {
	vertices = NULL;
	colors = NULL;
	texcoords = NULL;
	normals = NULL;
	indices = NULL;
}

P3d_Mesh::~P3d_Mesh() {
	if(vertices != NULL) free(vertices);
	if(colors != NULL) free(colors);
	if(texcoords != NULL) free(texcoords);
	if(normals != NULL) free(normals);
	if(indices != NULL) free(indices);
}

bool P3d_Mesh::load_mesh(FILE* fin) {
	fread(&num_vertices, sizeof(int), 1, fin);
	
	vertices = (float*) malloc(sizeof(float) * num_vertices * 3);
	fread(vertices, sizeof(float), num_vertices * 3, fin);

	normals = (float*) malloc(sizeof(float) * num_vertices * 3);
	fread(normals, sizeof(float), num_vertices * 3, fin);

	texcoords = (float*) malloc(sizeof(float) * num_vertices * 2);
	fread(texcoords, sizeof(float), num_vertices * 2, fin);

	fread(&num_faces, sizeof(int), 1, fin);
	num_indices = num_faces * 3;

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

	/*printf("face normals\n");
	for(i=0; i!=num_faces; i++) {
		print_vec3(glm::vec3(fnormals[indices[i*3 + 0] * 3 + 0], fnormals[indices[i*3 + 0] * 3 + 1], fnormals[indices[i*3 + 0] * 3 + 2]));
		print_vec3(glm::vec3(fnormals[indices[i*3 + 1] * 3 + 0], fnormals[indices[i*3 + 1] * 3 + 1], fnormals[indices[i*3 + 1] * 3 + 2]));
		print_vec3(glm::vec3(fnormals[indices[i*3 + 2] * 3 + 0], fnormals[indices[i*3 + 2] * 3 + 1], fnormals[indices[i*3 + 2] * 3 + 2]));
	}

	for(i=0; i!=num_faces; i++) {
		printf("calculating face normal\n");
		print_vec3(glm::vec3(vertices[indices[i*3 + 0] * 3 + 0], vertices[indices[i*3 + 0] * 3 + 1], vertices[indices[i*3 + 0] * 3 + 2]));
		print_vec3(glm::vec3(vertices[indices[i*3 + 1] * 3 + 0], vertices[indices[i*3 + 1] * 3 + 1], vertices[indices[i*3 + 1] * 3 + 2]));
		print_vec3(glm::vec3(vertices[indices[i*3 + 2] * 3 + 0], vertices[indices[i*3 + 2] * 3 + 1], vertices[indices[i*3 + 2] * 3 + 2]));
		printf("n:"); print_vec3(glm::vec3(fnormals[indices[i*3 + 2] * 3 + 0], fnormals[indices[i*3 + 2] * 3 + 1], fnormals[indices[i*3 + 2] * 3 + 2]));
	}*/

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, num_vertices * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof(int), indices, GL_STATIC_DRAW);

	if(FLAT_SHADING) {
		//flat shading
		glGenBuffers(1, &nb);
		glBindBuffer(GL_ARRAY_BUFFER, nb);
		glBufferData(GL_ARRAY_BUFFER, num_vertices * 3 * sizeof(float), fnormals, GL_STATIC_DRAW);
	}
	else {
		//smooth shading
		glGenBuffers(1, &nb);
		glBindBuffer(GL_ARRAY_BUFFER, nb);
		glBufferData(GL_ARRAY_BUFFER, num_vertices * 3 * sizeof(float), normals, GL_STATIC_DRAW);
	}

	return true;
}

void P3d_Mesh::render(GLuint shader_program) {
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	GLint posAttrib = glGetAttribLocation(shader_program, "inPosition");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, nb);
	GLint normAttrib = glGetAttribLocation(shader_program, "inNormal");
	glEnableVertexAttribArray(normAttrib);
	glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);

	//debug

}

//load call
P3d_Mesh *P3d_load_mesh(char* filename){
	FILE *fin = fopen(filename, "r");
	if(fin == NULL) {
		printf("error while opening %s\n",filename);
		return NULL;
	}

	int num_meshes;
	fread(&num_meshes, sizeof(int), 1, fin);
	printf("num_meshes : %d\n", num_meshes);

	P3d_Mesh *newmesh;
	int i;
	for(i=0; i!=num_meshes; i++) {
		newmesh = new P3d_Mesh();

		if(newmesh->load_mesh(fin) == false) {
			delete(newmesh);
			newmesh = NULL;
			printf("failed loading mesh\n");
		}
	}

	return newmesh;
}

/*
//------p3d file format-------//
num_meshes (int)
	num_vertices (int)

	v1.x, v1.y, v1.z //vertices (3 float)
	...
	vn.x, vn.y, vn.z

	n1.x, n1.y, n1.z //vertex normals (3 float)
	...
	nn.x, nn.y, nn.z

	t1.x, t1.y //texture coordinates (2 float)
	...
	tn.x, tn.y

	num_faces (int)
	i1, i2, i3 ... in //face indices (int)

	fn1.x, fn1.y, fn1.z //face normal (3 float)
	...
	fnn.x, fnn.y, fnn.z
*/