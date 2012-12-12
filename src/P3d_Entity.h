class P3d_Entity {
	public:
		P3d_Entity();
		void translate(float, float, float);
		void rotate(float, float, float);
		void move(const P3d_Vector3f&);
		void moveOriented(const P3d_Vector3f&);
		P3d_Vector4f& get_orient();
	protected:
		P3d_Vector3f position;
		P3d_Vector3f orientation;
		P3d_Vector4f orient;
};
