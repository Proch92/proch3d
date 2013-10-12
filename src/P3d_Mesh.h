#define SMOOTH true
#define FLAT false

struct Material
{
	float ambient;
	float diffuse;
	float specular;
	glm::vec4 color;
};

class P3d_Mesh {
	public:
		P3d_Mesh();
		~P3d_Mesh();
		void render(GLuint);
		bool load_mesh(FILE*);
	private:
		class Object {
			public:
				Object();
				~Object();
				bool load(FILE*);
				void render(GLuint);
			private:
				float* vertices;
				float* texcoords;
				float* colors;
				float* normals;
				float* fnormals;
				int* indices;

				GLuint vb;
				GLuint ib;
				GLuint cb;
				GLuint nb;
				GLuint vao;

				int material_index;
				int num_vertices;
				int num_faces;
				int num_indices;

				bool shading; //true = smooth, false = flat

				struct Material material;
		};

		Object *objects;
		int num_object;
};

P3d_Mesh *P3d_load_mesh(char*);