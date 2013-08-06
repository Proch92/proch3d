#include "proch3d.h"

long get_time() {
	struct timeval actual;
	gettimeofday(&actual, NULL);
	
	return (actual.tv_sec * 1000 + actual.tv_usec / 1000);
}

void p3d_delay(long ms) {
	usleep(ms * 1000);
}

void load_shader(const char* filename, GLuint shd) {
	FILE *file;
	
	file = fopen(filename, "r");
	if(file == NULL) {
		printf("failed to load shader\n");
		return;
	}
	
	fseek(file, 0, SEEK_END);
	long int size = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	GLchar* sourceBuffer = (GLchar*) new char[size+1];

	fread(sourceBuffer, 1, size, file);
	sourceBuffer[size] = 0;

	fclose(file);

	glShaderSource(shd, 1, (const GLchar**) &sourceBuffer, NULL);
	glCompileShader(shd);

	GLint status;
	glGetShaderiv(shd, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE) {
		printf("failed to compile shader\n");
	}
	char buffer[512];
	glGetShaderInfoLog(shd, 512, NULL, buffer);
	if(buffer[0] != '\0') printf("%s\n", buffer);
}

void print_mat4(const glm::mat4 &mat) {
	int i;
	for(i=0; i!=4; i++) {
		printf("%f,  %f,  %f,  %f\n", mat[i][0], mat[i][1], mat[i][2], mat[i][3]);
	}
}