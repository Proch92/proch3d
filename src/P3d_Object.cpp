#include "proch3d.h"

P3d_Object::P3d_Object() {
	hidden = false;
	mesh = NULL;
}

void P3d_Object::render(glm::mat4 &proj, glm::mat4 view) {
	if(hidden) return;

	update_model_matrix();
	
	GLuint uniProj = glGetUniformLocation(shader_program, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	GLuint uniView = glGetUniformLocation(shader_program, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

	GLuint uniModel = glGetUniformLocation(shader_program, "model");
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	GLuint uniRot = glGetUniformLocation(shader_program, "rot");
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(glm::mat4_cast(rotation)));

	//ambient light
	glm::vec4 ambientLight(1.0, 1.0, 1.0, 1.0);
	GLuint uniAmbient = glGetUniformLocation(shader_program, "ambientLight");
	glUniform4f(uniAmbient, ambientLight[0], ambientLight[1], ambientLight[2], ambientLight[3]);
	float ambientLightIntensity = 0.2;
	GLuint uniAmbientIntensity = glGetUniformLocation(shader_program, "ambientLightIntensity");
	glUniform1f(uniAmbientIntensity, ambientLightIntensity);

	//directional light
	glm::vec4 dirLightColor(0.3, 0.3, 0.3, 1.0);
	glm::vec4 dirLightDirection(1.0, 0.0, 0.0, 1.0);
	dirLightDirection = dirLightDirection * glm::mat4_cast(rotation);
	//print_vec4(dirLightDirection);
	GLuint uniDirLightColor = glGetUniformLocation(shader_program, "dirLightColor");
	glUniform4f(uniDirLightColor, dirLightColor[0], dirLightColor[1], dirLightColor[2], dirLightColor[3]);
	GLuint uniDirLightDirection = glGetUniformLocation(shader_program, "dirLightDirection");
	glUniform3f(uniDirLightDirection, dirLightDirection.x, dirLightDirection.y, dirLightDirection.z);

	//point lights
	int nPointLights = 2;

	glm::vec4 pointLightPosition[nPointLights];
	glm::vec4 pointLightColor[nPointLights];
	float fv_pointLightPosition[nPointLights * 4];
	float fv_pointLightColor[nPointLights * 4];

	pointLightPosition[0] = glm::vec4(0.0, -2.0, 1.5, 1.0);
	pointLightColor[0] = glm::vec4(1.0, 1.0, 1.0, 1.0);
	pointLightPosition[1] = glm::vec4(0.0, 1.5, -1.0, 1.0);
	pointLightColor[1] = glm::vec4(1.0, 1.0, 1.0, 1.0);

	for(int i=0; i!=nPointLights; i++) {
		pointLightPosition[i] = pointLightPosition[i] - glm::vec4(position, 1.0);
		pointLightPosition[i] = pointLightPosition[i] * glm::mat4_cast(rotation);
		//print_vec4(pointLightPosition);
		for(int j=0; j!=4; j++) {
			fv_pointLightPosition[i*4 + j] = pointLightPosition[i][j];
			fv_pointLightColor[i*4 + j] = pointLightColor[i][j];
		}
	}

	GLuint uniNPointLight = glGetUniformLocation(shader_program, "nPointLight");
	glUniform1i(uniNPointLight, nPointLights);
	GLuint uniPointLightPos = glGetUniformLocation(shader_program, "pointLightPos");
	glUniform4fv(uniPointLightPos, nPointLights, fv_pointLightPosition);
	GLuint uniPointLightColor = glGetUniformLocation(shader_program, "pointLightColor");
	glUniform4fv(uniPointLightColor, nPointLights, fv_pointLightColor);


	if(mesh != NULL)
		mesh->render(shader_program);
}

void P3d_Object::set_mesh(P3d_Mesh* m) {
	mesh = m;
}

void P3d_Object::set_shader_program(GLuint sp) {
	shader_program = sp;
}

/*void P3d_Object::load_cube(int n) {
	num_vertices = 8;
	float n2 = (float)n / 2;
	vertices = new float[24] {
		-n2, -n2, -n2,
		n2, -n2, -n2,
		n2, -n2, n2,
		-n2, -n2, n2,

		-n2, n2, -n2,
		n2, n2, -n2,
		n2, n2, n2,
		-n2, n2, n2
	};

	texcoords = new float[72] {
		0.0, 0.0,
		0.0, 1.0,
		1.0, 1.0,
		1.0, 1.0,
		1.0, 0.0,
		0.0, 0.0
	};
	int i;
	for(i=2; i!=7; i++)
		memcpy(&(texcoords[i*12]), texcoords, 12*sizeof(float));

	indices = new int[36] {
		0,1,2,
		2,3,0,

		4,5,6,
		6,7,4,

		3,7,6,
		6,2,3,

		0,4,7,
		7,3,0,

		1,5,4,
		4,0,1,

		2,6,5,
		5,1,2
	};
	num_indices = 36;

	colors = new float[32] {
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,

		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0
	};

	//creating gpu memory buffers
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, num_vertices * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * 2 * sizeof(int), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &cb);
	glBindBuffer(GL_ARRAY_BUFFER, cb);
	glBufferData(GL_ARRAY_BUFFER, num_vertices * 4 * sizeof(float), colors, GL_STATIC_DRAW);
}

void P3d_Object::load_tetrahedron() {
	num_vertices = 4;
	vertices = new float[12] {
		0, 0, 0,
		0.5, sqrtf(3)/2, 0,
		1.0, 0.0, 0.0,
		0.5, 1.0/3.0, sqrtf(2.0/3.0)
	};

	texcoords = new float[24] {
		0, 0,
		0.5, sqrtf(3)/2,
		1.0, 0.0
	};
	int i;
	for(i=2; i!=5; i++)
		memcpy(&(texcoords[i*6]), texcoords, 6*sizeof(float));

	indices = new int[12] {
		0, 2, 1,
		0, 3, 2,
		2, 3, 1,
		1, 3, 0
	};
	num_indices = 12;

	colors = new float[16] {
		1.0, 0.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		1.0, 0.0, 1.0, 1.0,
		0.0, 0.0, 0.0, 1.0
	};

	//creating gpu memory buffers
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, num_vertices * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * 2 * sizeof(int), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &cb);
	glBindBuffer(GL_ARRAY_BUFFER, cb);
	glBufferData(GL_ARRAY_BUFFER, num_vertices * 4 * sizeof(float), colors, GL_STATIC_DRAW);
}

void P3d_Object::load_doublepiramid() {
	num_vertices = 6;
	vertices = new float[18] {
		-0.5, -0.5, 0.0,
		-0.5, 0.5, 0.0,
		0.5, 0.5, 0.0,
		0.5, -0.5, 0.0,
		0.0, 0.0, 1.6,
		0.0, 0.0, -1.6
	};

	texcoords = new float[24] {
		0, 0,
		0.5, sqrtf(3)/2,
		1.0, 0.0
	};
	int i;
	for(i=2; i!=5; i++)
		memcpy(&(texcoords[i*6]), texcoords, 6*sizeof(float));

	indices = new int[24] {
		0, 4, 3,
		3, 4, 2,
		2, 4, 1,
		1, 4, 0,

		0, 3, 5,
		3, 2, 5,
		2, 1, 5,
		1, 0, 5
	};
	num_indices = 24;

	colors = new float[24] {
		1.0, 0.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		1.0, 0.0, 1.0, 1.0,
		1.0, 0.0, 1.0, 1.0,
		0.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 0.0, 1.0,
	};

	//creating gpu memory buffers
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, num_vertices * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * 2 * sizeof(int), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &cb);
	glBindBuffer(GL_ARRAY_BUFFER, cb);
	glBufferData(GL_ARRAY_BUFFER, num_vertices * 4 * sizeof(float), colors, GL_STATIC_DRAW);
}

void P3d_Object::load_test() {
}*/