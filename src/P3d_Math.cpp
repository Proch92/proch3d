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


// Vector3f ------------------------------------------------------------------------------------------
P3d_Vector3f::P3d_Vector3f() {
	x=0;
	y=0;
	z=0;
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
