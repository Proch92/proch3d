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

bool P3d_Mesh::load_mesh(char* filename) {
	glm::vec3 zero3f(0, 0, 0);
	glm::vec2 zero2f(0, 0);

	printf("loading %s\n", filename);
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals);
	if(scene == NULL) {
		printf("failed loading %s\n", filename);
		return false;
	}

	int num_meshes = scene->mNumMeshes;
	if(!(scene->HasMeshes())) {
		printf("no meshes in this scene!\n");
		return false;
	}
	else printf("num_meshes:%d\n", num_meshes);
	
	int num_materials = scene->mNumMaterials;
	printf("num materials:%d\n", num_materials);

	int i;
	for(i=0; i!=num_meshes; i++) {
		const aiMesh* mesh = scene->mMeshes[i];

		material_index = mesh->mMaterialIndex;
		
		num_vertices = mesh->mNumVertices;
		printf("num vertices:%d\n", num_vertices);

		bool has_tex = mesh->HasTextureCoords(0);
		bool has_norm = mesh->HasNormals();

		//vertices = (P3d_Vertex*) malloc(sizeof(P3d_Vertex) * num_vertices);
		vertices = (float*) malloc(sizeof(float) * num_vertices * 3);
		colors = (float*) malloc(sizeof(float) * num_vertices * 4);
		texcoords = (float*) malloc(sizeof(float) * num_vertices * 2);
		normals = (float*) malloc(sizeof(float) * num_vertices * 3);

		int j;
		for(j=0; j!=num_vertices; j++) {
			//vertices[j].set_position(glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z));
			vertices[j*3 + 0] = mesh->mVertices[j].x;
			vertices[j*3 + 1] = mesh->mVertices[j].y;
			vertices[j*3 + 2] = mesh->mVertices[j].z;
			
			if(has_tex) {
				//vertices[j].set_tex_coordinate(glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y));
				texcoords[j*3 + 0] = mesh->mTextureCoords[0][j].x;
				texcoords[j*3 + 1] = mesh->mTextureCoords[0][j].y;
			}
			else {
				//vertices[j].set_tex_coordinate(zero2f);
				texcoords[j*3 + 0] = zero2f.x;
				texcoords[j*3 + 1] = zero2f.y;
			}
			
			if(has_norm) {
				//vertices[j].set_normal(glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z));
				normals[j*3 + 0] = mesh->mNormals[j].x;
				normals[j*3 + 1] = mesh->mNormals[j].y;
				normals[j*3 + 2] = mesh->mNormals[j].z;
			}
			else {
				//vertices[j].set_normal(zero3f);
				normals[j*3 + 0] = zero3f.x;
				normals[j*3 + 1] = zero3f.y;
				normals[j*3 + 2] = zero3f.z;
			}

			colors[j*3 + 0] = rand() % 2;
			colors[j*3 + 1] = rand() % 2;
			colors[j*3 + 2] = rand() % 2;
		}

		num_faces = mesh->mNumFaces;
		printf("num_faces:%d\n", num_faces);
		indices = (int*) malloc(sizeof(int) * num_faces * 3);
		num_indices = num_faces * 3;
		printf("num_indicies: %d\n", num_indices);
		
		for(j=0; j!=num_faces; j++) {
			aiFace *face = &(mesh->mFaces[j]);
			if(face->mNumIndices != 3) {
				printf("num_indices per face != 3\n");
				return false;
			}
			indices[j*3 + 0] = face->mIndices[0];
			indices[j*3 + 1] = face->mIndices[1];
			indices[j*3 + 2] = face->mIndices[2];
		}
	}

	//fill vertex buffers
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

	return true;
}

void P3d_Mesh::render(GLuint shader_program) {
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	GLint posAttrib = glGetAttribLocation(shader_program, "inPosition");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, cb);
	GLint colAttrib = glGetAttribLocation(shader_program, "inColor");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
}

//load call
P3d_Mesh *P3d_load_mesh(char* filename){
	P3d_Mesh *newmesh = new P3d_Mesh();

	if(newmesh->load_mesh(filename) == false) {
		delete(newmesh);
		newmesh = NULL;
		printf("failed loading mesh\n");
	}

	return newmesh;
}