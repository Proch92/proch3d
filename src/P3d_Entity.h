class P3d_Entity {
	public:
		P3d_Entity();
		void translate(float, float, float);
		void rotate(float, float, float);
	protected:
		P3d_Vector3f position;
		P3d_Vector3f orientation;
};
