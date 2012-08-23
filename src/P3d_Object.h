class P3d_Object : public P3d_Entity {
	public:
		P3d_Object();
		
		void render();
		void set_color(const P3d_Color4f&);
		
		P3d_Color4f color;
	protected:
		bool hidden;
};
