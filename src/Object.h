class Object : public Entity {
	public:
		Object();
		
		void render();
		
		Color4f color;
	protected:
		bool hidden;
};
