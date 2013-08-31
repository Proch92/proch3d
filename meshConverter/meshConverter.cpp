#include "glm/glm.hpp"
#include "glm/gtx/normal.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "stdio.h"
#include "stdlib.h"

void print_vec3(const glm::vec3 &);
void print_mesh(struct _mesh*);

struct vertex {
	glm::vec3 v;
	glm::vec2 texcoord;
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

	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate);
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
				meshes[i].vertices[j].texcoord = glm::vec2(mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y);
			else
				meshes[i].vertices[j].texcoord = glm::vec2(0.0, 0.0);
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
			printf("calculating face normal\n");
			print_vec3(meshes[i].faces[j].v[0]->v);
			print_vec3(meshes[i].faces[j].v[1]->v);
			print_vec3(meshes[i].faces[j].v[2]->v);
			printf("n:"); print_vec3(meshes[i].faces[j].face_normal);
		}

		//generating vertex normals
		for(j=0; j!=meshes[i].num_faces; j++) {
			struct face &f = meshes[i].faces[j];

			int k;
			for(k=0; k!=3; k++) {
				if(f.v[k]->normal == glm::vec3(0.0, 0.0, 0.0)) {
					glm::vec3 n = f.face_normal;
					int nfound = 0;
					int ifound[100];
					//searching for adiacent faces
					int z;
					for(z=0; z!=meshes[i].num_faces && z!=j; z++) {
						struct face &f2 = meshes[i].faces[z];

						int y;
						for(y=0; y!=3; y++)
							if(f2.v[y]->v == f.v[k]->v) {
								n += f2.face_normal;

								ifound[nfound] = f2.index[y];
								nfound++;
							}
					}
					if(nfound > 100) printf("!!!!!!!!!!! nfound > 100 (%d) !!!!!!!!!!!!!!\n", nfound);
					else printf("%d\n", nfound);
					n = glm::normalize(n);

					f.v[k]->normal = n;
					for(z=0; z!=nfound; z++)
						meshes[i].vertices[ifound[z]].normal = n;
				}
			}
		}
	}
	print_mesh(meshes);

	//export to p3d file

	FILE *out = fopen(outname, "w");
	if(out == NULL) {
		printf("unable to open %s\n", outname);
		return -1;
	}

	fwrite(&num_meshes, sizeof(int), 1, out); //num_meshes

	for(i=0; i!=num_meshes; i++) {
		fwrite(&meshes[i].num_vertices, sizeof(int), 1, out); //num_vertices

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
		for(j=0; j!=meshes[i].num_vertices; j++) { //texture coordinate
			fbuffer[fi++] = meshes[i].vertices[j].texcoord.x;
			fbuffer[fi++] = meshes[i].vertices[j].texcoord.y;
		}
		fwrite(fbuffer, sizeof(float), meshes[i].num_vertices * 2, out);

		fwrite(&meshes[i].num_faces, sizeof(int), 1, out); //num_faces

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