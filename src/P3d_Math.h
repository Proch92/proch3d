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
