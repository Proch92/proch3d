struct P3d_frustum {
	int left, right, bottom, top, near, far;
};

class P3d_Camera : public P3d_Entity {
	public:
		P3d_Camera();
		void camera_glulookat();
		void set_frustum(struct P3d_frustum);
		void set_frustum(int, int, int, int, int, int);
		struct P3d_frustum* get_frustum();
	private:
		struct P3d_frustum frustum;
};
