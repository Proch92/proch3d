#include "proch3d.h"

P3d_Object::P3d_Object() {
	hidden = false;
	mesh = NULL;
	num_meshes = 0;
}

void P3d_Object::render(glm::mat4 &proj, glm::mat4 view, glm::vec3 cameraPos) {
	if(hidden) return;

	update_model_matrix();
	
	GLuint uniProj = glGetUniformLocation(shader_program, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	GLuint uniView = glGetUniformLocation(shader_program, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

	GLuint uniModel = glGetUniformLocation(shader_program, "model");
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	//camera position
	GLuint uniCamera = glGetUniformLocation(shader_program, "cameraPos");
	glUniform3f(uniCamera, -cameraPos.x, -cameraPos.y, -cameraPos.z);

	//ambient light
	glm::vec4 ambientLight(1.0, 1.0, 1.0, 1.0);
	GLuint uniAmbient = glGetUniformLocation(shader_program, "ambientLight");
	glUniform4f(uniAmbient, ambientLight[0], ambientLight[1], ambientLight[2], ambientLight[3]);
	float ambientLightIntensity = 0.3;
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
	float pointLightAttenuation[nPointLights];

	pointLightPosition[0] = glm::vec4(0.0, -15.0, 1.5, 1.0);
	pointLightColor[0] = glm::vec4(1.0, 1.0, 1.0, 1.0);
	pointLightPosition[1] = glm::vec4(0.0, 1.5, 1.0, 1.0);
	pointLightColor[1] = glm::vec4(0.0, 0.0, 1.0, 1.0);

	for(int i=0; i!=nPointLights; i++) {
		pointLightPosition[i] = pointLightPosition[i] - glm::vec4(position, 1.0);
		pointLightPosition[i] = pointLightPosition[i] * glm::mat4_cast(rotation);
		//print_vec4(pointLightPosition);
		for(int j=0; j!=4; j++) {
			fv_pointLightPosition[i*4 + j] = pointLightPosition[i][j];
			fv_pointLightColor[i*4 + j] = pointLightColor[i][j];
		}

		pointLightAttenuation[i] = 25.0;
	}

	GLuint uniNPointLight = glGetUniformLocation(shader_program, "nPointLight");
	glUniform1i(uniNPointLight, nPointLights);
	GLuint uniPointLightPos = glGetUniformLocation(shader_program, "pointLightPos");
	glUniform4fv(uniPointLightPos, nPointLights, fv_pointLightPosition);
	GLuint uniPointLightColor = glGetUniformLocation(shader_program, "pointLightColor");
	glUniform4fv(uniPointLightColor, nPointLights, fv_pointLightColor);
	GLuint uniPointLightCAttenuation = glGetUniformLocation(shader_program, "pointLightAttenuation");
	glUniform1fv(uniPointLightCAttenuation, nPointLights, pointLightAttenuation);


	if(mesh != NULL)
		mesh->render(shader_program);
}

void P3d_Object::set_mesh(P3d_Mesh* m) {
	mesh = m;
}

void P3d_Object::set_shader_program(GLuint sp) {
	shader_program = sp;
}