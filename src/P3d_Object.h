class P3d_Object : public P3d_Entity {
	public:
		P3d_Object();
		
		void render(glm::mat4&);
		void set_mesh(P3d_Mesh*);
		void set_shader_program(GLuint);

		void load_cube(int);
		void load_tetrahedron();
		void load_test();
		
		float *vertices;
		int *indices;
		float *texcoords;
		float *colors;

		int num_vertices;
		int num_indices;

		GLuint vb;
		GLuint ib;
		GLuint cb;
		GLuint vao;

		GLuint shader_program;
	protected:
		bool hidden;
		P3d_Mesh *mesh;
};
