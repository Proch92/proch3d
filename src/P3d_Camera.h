struct P3d_Perspective {
	float fov;
	float aspect_ratio;
	float near;
	float far;
};

class P3d_Camera : public P3d_Entity {
	public:
		P3d_Camera();
		glm::mat4 get_view_matrix();

		glm::mat4 projectionMatrix;
	private:
		struct P3d_Perspective persp;
};
