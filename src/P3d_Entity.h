#define FRONT glm::vec3(0.0, 0.0, -1.0)
#define UP glm::vec3(0.0, 1.0, 0.0)
#define RIGHT glm::vec3(1.0, 0.0, 0.0)

class P3d_Entity {
	public:
		P3d_Entity();
		void translate(float, float, float);
		void translate(const glm::vec3&);
		void set_position(glm::vec3);
		void rotate(float, float, float);
		void rotate(float, glm::vec3);
		void orientedMove(glm::vec3);
		void update_model_matrix();
		glm::vec3 get_position();
		glm::vec3 get_orientation();
		glm::quat get_rotation();
		
		glm::mat4 modelMatrix;
	protected:
		glm::vec3 position;
		glm::quat rotation;

		bool modelChanged;
};
