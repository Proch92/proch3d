class Entity {
	public:
		Entity();
		void translate(float, float, float);
		void rotate(float, float, float);
	protected:
		Matrix4f matrix;
		
		Vector3f position;
		Vector3f orientation;
};
