#include "proch3d.h"
#include <glm/gtx/norm.hpp>

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

void print_vec3(const glm::vec3 &vec) {
	printf("[%f, %f, %f]\n", vec.x, vec.y, vec.z);
}

void print_vec4(const glm::vec4 &vec) {
	printf("[%f, %f, %f, %f]\n", vec.x, vec.y, vec.z, vec[3]);
}

glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest){
	start = glm::normalize(start);
	dest = glm::normalize(dest);

	float cosTheta = glm::dot(start, dest);
	glm::vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f){
		// special case when vectors in opposite directions :
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		// This implementation favors a rotation around the Up axis,
		// since it's often what you want to do.
		rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
		if (glm::length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
			rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = glm::normalize(rotationAxis);
		return glm::angleAxis(180.0f, rotationAxis);
	}

	// Implementation from Stan Melax's Game Programming Gems 1 article
	rotationAxis = glm::cross(start, dest);

	float s = glm::sqrt( (1+cosTheta)*2 );
	float invs = 1 / s;

	return glm::quat(
		s * 0.5f, 
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);
}