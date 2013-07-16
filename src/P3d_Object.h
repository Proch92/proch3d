class P3d_Object : public P3d_Entity {
	public:
		P3d_Object();
		
		void render();
		void set_color(const P3d_Color4f&);
		void set_mesh(P3d_Mesh*);
		
		P3d_Color4f color;
	protected:
		bool hidden;
		P3d_Mesh *mesh;
};
