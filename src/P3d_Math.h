const float DEG2RAD = 0.017453294; //3.141593 / 180

class P3d_Vector3f {
	public:
		P3d_Vector3f();
		P3d_Vector3f(float, float, float);
		void operator = (const P3d_Vector3f&);
		P3d_Vector3f operator * (const P3d_Vector3f&);
		void operator += (const P3d_Vector3f&);
		void normalize();
		float get_magnitude();
		float x;
		float y;
		float z;
	private:
		
};

class P3d_Vector4f {
	public:
		P3d_Vector4f();
		P3d_Vector4f(float, float, float, float);
		void operator = (const P3d_Vector4f&);
		P3d_Vector4f operator * (const P3d_Vector4f&);
		void operator += (const P3d_Vector4f&);
		void normalize();
		float get_magnitude();
		float& operator [] (int);
		float data[4];
	private:
};

class P3d_Matrix4f {
	public:
		P3d_Matrix4f();
		
		P3d_Matrix4f operator * (P3d_Matrix4f&);
		P3d_Vector4f operator * (const P3d_Vector4f&);
		void operator = (const P3d_Matrix4f&);
		float& operator [] (int);
		void show();
		float* get_data();
	private:
		float data[16];
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
