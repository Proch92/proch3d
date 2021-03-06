class P3d_Object : public P3d_Entity {
	public:
		P3d_Object();
		
		void render(glm::mat4&, glm::mat4, glm::vec3);
		void set_mesh(P3d_Mesh*);
		void set_shader_program(GLuint);

		GLuint shader_program;
	protected:
		bool hidden;
		int num_meshes;
		P3d_Mesh *mesh;
};
