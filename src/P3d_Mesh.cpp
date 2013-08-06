#include "proch3d.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

P3d_Mesh::P3d_Mesh() {
}

P3d_Mesh::~P3d_Mesh() {
}

bool P3d_Mesh::load_mesh(char* filename) {
	vertices = NULL;
	indices = NULL;

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

		vertices = (P3d_Vertex*) malloc(sizeof(P3d_Vertex) * num_vertices);

		int j;
		for(j=0; j!=num_vertices; j++) {
			vertices[j].set_position(glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z));
			
			if(has_tex) vertices[j].set_tex_coordinate(glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y));
			else vertices[j].set_tex_coordinate(zero2f);
			
			if(has_norm) vertices[j].set_normal(glm::vec3(mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z));
			else vertices[j].set_normal(zero3f);
		}

		num_faces = mesh->mNumFaces;
		printf("num_faces:%d\n", num_faces);
		indices = (int*) malloc(sizeof(int) * num_faces * 3);
		int k=0;

		for(j=0; j!=num_faces; j++) {
			aiFace *face = &(mesh->mFaces[j]);
			if(face->mNumIndices != 3) {
				printf("num_indices per face != 3\n");
				return false;
			}
			indices[k] = face->mIndices[0];
			indices[k+1] = face->mIndices[1];
			indices[k+2] = face->mIndices[2];
			k+=3;
		}
	}

	return true;
}

void P3d_Mesh::render() {

}

//load call
P3d_Mesh *P3d_load_mesh(char* filename){
	P3d_Mesh *newmesh = (P3d_Mesh*) malloc(sizeof(P3d_Mesh));

	if(newmesh->load_mesh(filename) == false) {
		if(newmesh->vertices != NULL) free(newmesh->vertices);
		if(newmesh->indices != NULL) free(newmesh->indices);
		free(newmesh);
		newmesh = NULL;
	}

	return newmesh;
}