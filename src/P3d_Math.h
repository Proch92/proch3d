const float DEG2RAD = 3.141593f / 180;

class Matrix4f {
	public:
		Matrix4f();
		
		Matrix4f operator * (Matrix4f&);
		void operator = (const Matrix4f&);
		
		float& operator [] (int);
		
		float* get_data();
	private:
		float data[16];
};

class Vector3f {
	public:
		Vector3f();
		float x;
		float y;
		float z;
	private:
		
};

class Color4f {
	public:
		Color4f();
		float r;
		float g;
		float b;
		float a;
	private:
		
};
