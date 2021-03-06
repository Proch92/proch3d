#include "glm/glm.hpp"
#include "glm/gtx/normal.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "stdio.h"
#include "stdlib.h"

void print_vec3(const glm::vec3 &);
void print_mesh(struct _mesh*);
bool vequal(struct vertex*, struct vertex*);

struct vertex {
	glm::vec3 v;
	glm::vec2 UV;
	glm::vec3 normal;
};

struct face {
	glm::vec3 face_normal;

	struct vertex *v[3];

	int index[3];
};

struct _mesh {
	struct face *faces;
	struct vertex *vertices;

	int num_vertices, num_materials, num_faces, num_indices;
};

int num_meshes;

int main(int argc, char **argv)
{
	char* filename = argv[1];
	char* outname = argv[2];

	printf("loading %s\n", filename);
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	if(scene == NULL) {
		printf("failed loading %s\n", filename);
		return false;
	}

	num_meshes = scene->mNumMeshes;
	if(!(scene->HasMeshes())) {
		printf("no meshes in this scene!\n");
		return false;
	}
	else printf("num_meshes:%d\n", num_meshes);
	struct _mesh *meshes = (struct _mesh*) malloc(sizeof(struct _mesh) * num_meshes);
	
	//num_materials = scene->mNumMaterials;
	//printf("num materials:%d\n", num_materials);

	int i;
	for(i=0; i!=num_meshes; i++) {
		const aiMesh* mesh = scene->mMeshes[i];

		bool has_tex = mesh->HasTextureCoords(0);

		//material_index = mesh->mMaterialIndex;
		
		meshes[i].num_vertices = mesh->mNumVertices;
		printf("num vertices:%d\n", meshes[i].num_vertices);
		meshes[i].vertices = (struct vertex*) malloc(sizeof(struct vertex) * meshes[i].num_vertices);

		int j;
		for(j=0; j!=meshes[i].num_vertices; j++) {
			meshes[i].vertices[j].v = glm::vec3(mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z);
			
			if(has_tex)
				meshes[i].vertices[j].UV = glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);
			else
				meshes[i].vertices[j].UV = glm::vec2(0.0, 0.0);
		}

		meshes[i].num_faces = mesh->mNumFaces;
		printf("num_faces:%d\n", meshes[i].num_faces);
		meshes[i].num_indices = meshes[i].num_faces * 3;
		printf("num_indicies: %d\n", meshes[i].num_indices);
		
		meshes[i].faces = (struct face*) malloc(sizeof(struct face) * meshes[i].num_faces);
		
		for(j=0; j!=meshes[i].num_faces; j++) {
			aiFace *face = &(mesh->mFaces[j]);
			if(face->mNumIndices != 3) {
				printf("num_indices per face != 3\n");
				return false;
			}

			meshes[i].faces[j].index[0] = face->mIndices[0];
			meshes[i].faces[j].index[1] = face->mIndices[1];
			meshes[i].faces[j].index[2] = face->mIndices[2];

			meshes[i].faces[j].v[0] = &meshes[i].vertices[meshes[i].faces[j].index[0]];
			meshes[i].faces[j].v[1] = &meshes[i].vertices[meshes[i].faces[j].index[1]];
			meshes[i].faces[j].v[2] = &meshes[i].vertices[meshes[i].faces[j].index[2]];

			//calculating face normal
			meshes[i].faces[j].face_normal = glm::triangleNormal(meshes[i].faces[j].v[0]->v, meshes[i].faces[j].v[1]->v, meshes[i].faces[j].v[2]->v);
		}

		//generating vertex normals
		for(j=0; j!=meshes[i].num_vertices; j++) {
			struct vertex *actual_vertex = &meshes[i].vertices[j];
			actual_vertex->normal = glm::vec3(0.0, 0.0, 0.0);

			for(int k=0; k!=meshes[i].num_faces; k++) {
				struct face *match_face = &meshes[i].faces[k];
				for(int h=0; h!=3; h++) {
					struct vertex *match_vertex = match_face->v[h];

					if(vequal(actual_vertex, match_vertex))
						actual_vertex->normal += match_face->face_normal;
				}
			}

			actual_vertex->normal = glm::normalize(actual_vertex->normal);
		}
	}
	//print_mesh(meshes);

	//export to p3d file

	FILE *out = fopen(outname, "w");
	if(out == NULL) {
		printf("unable to open %s\n", outname);
		return -1;
	}

	fwrite(&num_meshes, sizeof(int), 1, out); //num_meshes

	for(i=0; i!=num_meshes; i++) {
		fwrite(&meshes[i].num_vertices, sizeof(int), 1, out); //num_vertices

		printf("%d\n", meshes[i].num_faces);
		fwrite(&meshes[i].num_faces, sizeof(int), 1, out); //num_faces

		float* fbuffer = (float*) malloc(sizeof(float) * 3 * meshes[i].num_vertices);
		
		int fi = 0;

		int j;
		for(j=0; j!=meshes[i].num_vertices; j++) { //vertices
			fbuffer[fi++] = meshes[i].vertices[j].v.x;
			fbuffer[fi++] = meshes[i].vertices[j].v.y;
			fbuffer[fi++] = meshes[i].vertices[j].v.z;
		}
		fwrite(fbuffer, sizeof(float), meshes[i].num_vertices * 3, out);

		fi = 0;
		for(j=0; j!=meshes[i].num_vertices; j++) { //vertex normals
			fbuffer[fi++] = meshes[i].vertices[j].normal.x;
			fbuffer[fi++] = meshes[i].vertices[j].normal.y;
			fbuffer[fi++] = meshes[i].vertices[j].normal.z;
		}
		fwrite(fbuffer, sizeof(float), meshes[i].num_vertices * 3, out);

		fi = 0;
		for(j=0; j!=meshes[i].num_vertices; j++) { //UV coordinate
			fbuffer[fi++] = meshes[i].vertices[j].UV.x;
			fbuffer[fi++] = meshes[i].vertices[j].UV.y;
		}
		fwrite(fbuffer, sizeof(float), meshes[i].num_vertices * 2, out);

		int* ibuffer = (int*) malloc(sizeof(int) * meshes[i].num_indices);
		int ii = 0;
		for(j=0; j!=meshes[i].num_faces; j++) { //indices
			ibuffer[ii++] = meshes[i].faces[j].index[0];
			ibuffer[ii++] = meshes[i].faces[j].index[1];
			ibuffer[ii++] = meshes[i].faces[j].index[2];
		}
		fwrite(ibuffer, sizeof(int), meshes[i].num_faces * 3, out);

		free(ibuffer);
		free(fbuffer);
		fbuffer = (float*) malloc(sizeof(float) * 3 * meshes[i].num_faces);

		fi = 0;
		for(j=0; j!=meshes[i].num_faces; j++) { //face normals
			fbuffer[fi++] = meshes[i].faces[j].face_normal.x;
			fbuffer[fi++] = meshes[i].faces[j].face_normal.y;
			fbuffer[fi++] = meshes[i].faces[j].face_normal.z;
		}
		fwrite(fbuffer, sizeof(float), meshes[i].num_faces * 3, out);
		free(fbuffer);
	}

	fclose(out);

	return 0;
}

void print_vec3(const glm::vec3 &vec) {
	printf("[%f, %f, %f]\n", vec.x, vec.y, vec.z);
}

void print_mesh(struct _mesh* meshes) {
	int i;
	for(i=0; i!=num_meshes; i++) {
		printf("mesh n°%d\n", i);

		printf("vertices:\n");
		int j;
		for(j=0; j!=meshes[i].num_vertices; j++)
			print_vec3(meshes[i].vertices[j].v);

		printf("normals:\n");
		for(j=0; j!=meshes[i].num_vertices; j++)
			print_vec3(meshes[i].vertices[j].normal);

		printf("faces:\n");
		for(j=0; j!=meshes[i].num_faces; j++) {
			printf("%d:\n", j);
			printf("  %d\n", meshes[i].faces[j].index[0]);
			printf("  %d\n", meshes[i].faces[j].index[1]);
			printf("  %d\n", meshes[i].faces[j].index[2]);
			printf("face normal: "); print_vec3(meshes[i].faces[j].face_normal);
		}
	}
}

bool vequal(struct vertex* a, struct vertex* b) {
	return (a->v.x == b->v.x && a->v.y == b->v.y && a->v.z == b->v.z);
}

/*
//------p3d file format-------//
num_meshes (int)
	num_vertices (int)

	num_faces (int)

	//vertex attributes
	v1.x, v1.y, v1.z //vertices (3 float)
	...
	vn.x, vn.y, vn.z

	n1.x, n1.y, n1.z //vertex normals (3 float)
	...
	nn.x, nn.y, nn.z

	t1.x, t1.y //UV coordinates (2 float)
	...
	tn.x, tn.y
	
	//face attributes
	i1, i2, i3 ... in //face indices (int)

	fn1.x, fn1.y, fn1.z //face normal (3 float)
	...
	fnn.x, fnn.y, fnn.z
*/