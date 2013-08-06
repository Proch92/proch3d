class P3d_Vertex {
	public:
		P3d_Vertex(const glm::vec3&, const glm::vec2&, const glm::vec3&);
		void set_position(const glm::vec3&);
		void set_tex_coordinate(const glm::vec2&);
		void set_normal(const glm::vec3&);
		glm::vec3 pos;
		glm::vec2 tex;
		glm::vec3 norm;
};