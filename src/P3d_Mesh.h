class P3d_Mesh {
	public:
		P3d_Mesh();
		~P3d_Mesh();
		void render(GLuint);
		bool load_mesh(FILE*);

		//P3d_Vertex* vertices;
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
	private:
		int material_index;
		int num_vertices;
		int num_faces;
		int num_indices;
};

P3d_Mesh *P3d_load_mesh(char*);