#include "../src/proch3d.h"

void draw_scene();
void load_media();

GLuint vertex_shd;
GLuint fragment_shd;
GLuint shaderProgram;

P3d_Object obj;

P3d_Mesh *mesh;

bool running = true;

int main(int argc, char **argv) {
	printf("start\n");

	P3d_Window window;
	window.create();
	printf("window created\n");

	glewExperimental = GL_TRUE;
	GLuint err = glewInit();
	if(err != GLEW_OK) {
		printf("glew initialisation failed\n");
		return -1;
	}
	printf("glew initiated\n");

	glEnable(GL_DEPTH_TEST);
	
	P3d_InputManager input_manager(&window.sf_window);
	
	P3d_Renderer renderer;
	renderer.set_current_window(&window.sf_window);
	renderer.set_max_fps(60);
	renderer.show_xyz_axis(true);
	
	P3d_Camera camera0;
	renderer.set_current_camera(&camera0);
	
	printf("loading media\n");
	load_media();
	printf("media loaded\n");

	//create shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex_shd);
	glAttachShader(shaderProgram, fragment_shd);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	printf("shader program created\n");

	//obj.set_mesh(mesh);
	obj.load_tetrahedron();
	obj.set_shader_program(shaderProgram);
	obj.translate(-0.5, 0.5, -5.0);
	obj.rotate(0.0, glm::vec3(1.0, 0.0, 0.0));
	
	sf::Event event;
	
	while(running) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//draw_scene();
		obj.render(camera0.projectionMatrix);

		renderer.check_fps();
		renderer.update_screen();
		
		
		while(input_manager.poll_event(event)) {
			if (event.Type == sf::Event::Closed)
				running = false;
			else if(event.Type == sf::Event::KeyPressed)
				switch(event.Key.Code) {
					case sf::Key::Escape:
						running = false;
						break;
				}
		}
	}
}

void draw_scene() {
	//obj.render();
}

void load_media() {
	//mesh = P3d_load_mesh("examples/prova.obj");

	vertex_shd = glCreateShader(GL_VERTEX_SHADER);
	load_shader("examples/shaders/vertex.shd", vertex_shd);
	
	fragment_shd = glCreateShader(GL_FRAGMENT_SHADER);
	load_shader("examples/shaders/fragment.shd", fragment_shd);
}