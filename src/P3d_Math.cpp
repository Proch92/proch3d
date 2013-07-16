#include "proch3d.h"

P3d_Matrix4f::P3d_Matrix4f() {
	int i;
	for(i=0; i!=16; i++)
		if(i % 5) data[i] = 0;
		else data[i] = 1;
}

P3d_Matrix4f P3d_Matrix4f::operator * (P3d_Matrix4f &m) { //NOT TESTED
	P3d_Matrix4f result;
	
	int i, j;
	
	for(i=0; i!=4; i++)
		for(j=0; j!=4; j++)
			result[i + (j * 4)] = (data[i + (j * 4)] * m[(j * 4) + i]) + (data[i + (j + 1) * 4] * m[(j + 1) * 4 + i]) + (data[i + (j + 2) * 4] * m[(j + 2) * 4 + i]) + (data[i + (j + 3) * 4] * m[(j + 3) * 4 + i]);
	
	return result;
}

P3d_Vector4f P3d_Matrix4f::operator * (const P3d_Vector4f &v4f) {
	P3d_Vector4f result;
	
	int i, j;
	for(i=0; i!=4; i++) {
		for(j=0; j!=4; j++) {
			result[i] += v4f.data[j] * data[(i*4) + j];
		}
	}
	
	return result;
}

void P3d_Matrix4f::operator = (const P3d_Matrix4f &m) {
	int i;
	for(i=0; i!=16; i++)
		data[i] = ((P3d_Matrix4f)m)[i];
}

float& P3d_Matrix4f::operator [] (int index) {
	return data[index];
}

float* P3d_Matrix4f::get_data() {
	return data;
}

void P3d_Matrix4f::show() {
	printf("%f ", data[0]);
	printf("%f ", data[4]);
	printf("%f ", data[8]);
	printf("%f ", data[12]);
	printf("\n");
	printf("%f ", data[1]);
	printf("%f ", data[5]);
	printf("%f ", data[9]);
	printf("%f ", data[13]);
	printf("\n");
	printf("%f ", data[2]);
	printf("%f ", data[6]);
	printf("%f ", data[10]);
	printf("%f ", data[14]);
	printf("\n");
	printf("%f ", data[3]);
	printf("%f ", data[7]);
	printf("%f ", data[11]);
	printf("%f ", data[15]);
	printf("\n");
}

// P3d_Vector4f ------------------------------------------------------------------------------------------
P3d_Vector4f::P3d_Vector4f() {
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	data[3] = 1;
}

P3d_Vector4f::P3d_Vector4f(float d0, float d1, float d2, float d3) {
	data[0] = d0;
	data[1] = d1;
	data[2] = d2;
	data[3] = d3;
}

void P3d_Vector4f::normalize() {
	float magnitude = get_magnitude();
	data[0] /= magnitude;
	data[1] /= magnitude;
	data[2] /= magnitude;
	data[3] /= magnitude;
}

float P3d_Vector4f::get_magnitude() {
	return sqrtf((data[0] * data[0]) + (data[1] * data[1]) + (data[2] * data[2]) + (data[3] * data[3]));
}

void P3d_Vector4f::operator = (const P3d_Vector4f& v) {
	data[0] = v.data[0];
	data[1] = v.data[1];
	data[2] = v.data[2];
	data[3] = v.data[3];
}

P3d_Vector4f P3d_Vector4f::operator * (const P3d_Vector4f& v) {
	P3d_Vector4f result;
	
	result.data[0] = data[0] * v.data[0];
	result.data[1] = data[1] * v.data[1];
	result.data[2] = data[2] * v.data[2];
	result.data[3] = data[3] * v.data[3];
	
	return result;
}

void P3d_Vector4f::operator += (const P3d_Vector4f& v) {
	data[0] += v.data[0];
	data[1] += v.data[1];
	data[2] += v.data[2];
	data[3] += v.data[3];
}

float& P3d_Vector4f::operator [] (int index) {
	return data[index];
}

// Vector2f ------------------------------------------------------------------------------------------
P3d_Vector2f::P3d_Vector2f() {
	x = 0;
	y = 0;
}

P3d_Vector2f::P3d_Vector2f(float X, float Y) {
	x=X;
	y=Y;
}

void P3d_Vector2f::normalize() {
	float magnitude = get_magnitude();
	x /= magnitude;
	y /= magnitude;
}

float P3d_Vector2f::get_magnitude() {
	return sqrtf((x * x) + (y * y));
}

void P3d_Vector2f::operator = (const P3d_Vector2f& v) {
	x = v.x;
	y = v.y;
}

P3d_Vector2f P3d_Vector2f::operator * (const P3d_Vector2f& v) {
	P3d_Vector2f result;
	
	result.x = x * v.x;
	result.y = y * v.y;
	
	return result;
}

void P3d_Vector2f::operator += (const P3d_Vector2f& v) {
	x += v.x;
	y += v.y;
}

// Vector3f ------------------------------------------------------------------------------------------
P3d_Vector3f::P3d_Vector3f() {
	x = 0;
	y = 0;
	z = 1;
}

P3d_Vector3f::P3d_Vector3f(float X, float Y, float Z) {
	x=X;
	y=Y;
	z=Z;
}

void P3d_Vector3f::normalize() {
	float magnitude = get_magnitude();
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
}

float P3d_Vector3f::get_magnitude() {
	return sqrtf((x * x) + (y * y) + (z * z));
}

void P3d_Vector3f::operator = (const P3d_Vector3f& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}

P3d_Vector3f P3d_Vector3f::operator * (const P3d_Vector3f& v) {
	P3d_Vector3f result;
	
	result.x = x * v.x;
	result.y = y * v.y;
	result.z = z * v.z;
	
	return result;
}

void P3d_Vector3f::operator += (const P3d_Vector3f& v) {
	x += v.x;
	y += v.y;
	z += v.z;
}

// Color4f ------------------------------------------------------------------------------------------
P3d_Color4f::P3d_Color4f() {
	r=0;
	g=0;
	b=0;
	a=0;
}

P3d_Color4f::P3d_Color4f(float R, float G, float B, float A) {
	r=R;
	g=G;
	b=B;
	a=A;
}

void P3d_Color4f::operator = (const P3d_Color4f &new_color) {
	r = new_color.r;
	g = new_color.g;
	b = new_color.b;
	a = new_color.a;
};
