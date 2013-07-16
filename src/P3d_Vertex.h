class P3d_Vertex {
	public:
		P3d_Vertex(const P3d_Vector3f&, const P3d_Vector2f&, const P3d_Vector3f&);
		void set_position(const P3d_Vector3f&);
		void set_tex_coordinate(const P3d_Vector2f&);
		void set_normal(const P3d_Vector3f&);
		P3d_Vector3f pos;
		P3d_Vector2f tex;
		P3d_Vector3f norm;
};