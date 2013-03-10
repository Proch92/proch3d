class P3d_Entity {
	public:
		P3d_Entity();
		void translate(float, float, float);
		void translate(const P3d_Vector3f&);
		void rotate(float, float, float);
	protected:
		P3d_Vector3f position;
		P3d_Vector3f orientation;
};
