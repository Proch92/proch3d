const float DEG2RAD = 3.141593f / 180;

class P3d_Matrix4f {
	public:
		P3d_Matrix4f();
		
		P3d_Matrix4f operator * (P3d_Matrix4f&);
		void operator = (const P3d_Matrix4f&);
		
		float& operator [] (int);
		
		float* get_data();
	private:
		float data[16];
};

class P3d_Vector3f {
	public:
		P3d_Vector3f();
		float x;
		float y;
		float z;
	private:
		
};

class P3d_Color4f {
	public:
		P3d_Color4f();
		P3d_Color4f(float, float, float, float);
		void operator = (const P3d_Color4f&);
		float r;
		float g;
		float b;
		float a;
	private:
		
};
