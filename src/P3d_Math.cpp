#include "proch3d.h"

Matrix4f::Matrix4f() {
	int i;
	for(i=0; i!=16; i++)
		if(i % 5) data[i] = 0;
		else data[i] = 1;
}

Matrix4f Matrix4f::operator * (Matrix4f &m) { //NOT TESTED
	Matrix4f result;
	
	int i, j;
	
	for(i=0; i!=4; i++)
		for(j=0; j!=4; j++)
			result[i + (j * 4)] = (data[i + (j * 4)] * m[(j * 4) + i]) + (data[i + (j + 1) * 4] * m[(j + 1) * 4 + i]) + (data[i + (j + 2) * 4] * m[(j + 2) * 4 + i]) + (data[i + (j + 3) * 4] * m[(j + 3) * 4 + i]);
	
	return result;
}

void Matrix4f::operator = (const Matrix4f &m) {
	int i;
	for(i=0; i!=16; i++)
		data[i] = ((Matrix4f)m)[i];
}

float& Matrix4f::operator [] (int index) {
	return data[index];
}

float* Matrix4f::get_data() {
	return data;
}
