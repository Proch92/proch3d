struct P3d_Perspective {
	float fov;
	float aspect_ratio;
	float near;
	float far;
};

class P3d_Camera : public P3d_Entity {
	public:
		P3d_Camera();
		void update_model_matrix();

		glm::mat4 projectionMatrix;
		glm::mat4 lookAt;
	private:
		struct P3d_Perspective persp;
};
