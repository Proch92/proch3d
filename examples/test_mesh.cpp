#include "../src/proch3d.h"

void draw_scene();
void load_media();

GLuint vertex_shd;
GLuint fragment_shd;
GLuint shaderProgram;

P3d_Object obj;

P3d_Mesh *mesh;

bool running = true;

struct keymap {
	bool w,s,a,d;
} kmap;
bool lbool, kbool, jbool;
glm::vec2 mousePos;

int main(int argc, char **argv) {
	printf("start\n");

	kmap.w = kmap.s = kmap.a = kmap.d = false;
	lbool = kbool = jbool = false;
	mousePos = glm::vec2(DEFAULT_SCREEN_WIDTH/2.0, DEFAULT_SCREEN_HEIGHT/2.0);

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

	camera0.update_model_matrix();
	
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

	obj.set_mesh(mesh);
	obj.set_shader_program(shaderProgram);

	camera0.translate(glm::vec3(0.0, -5.0, 0.0));
	
	sf::Event event;
	
	while(running) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if(kmap.w)
			camera0.orientedMove(glm::vec3(0.2, 0.0, 0.0));
		if(kmap.s)
			camera0.orientedMove(glm::vec3(-0.2, 0.0, 0.0));
		if(kmap.a)
			camera0.orientedMove(glm::vec3(0.0, -0.2, 0.0));
		if(kmap.d)
			camera0.orientedMove(glm::vec3(0.0, 0.2, 0.0));

		if(kbool)
			obj.rotate(0.5f, glm::vec3(0.0, 0.0, 1.0));
		if(jbool)
			obj.rotate(-0.5f, glm::vec3(0.0, 0.0, 1.0));
		
		//obj.rotate(0.5f, glm::vec3(0.0, 0.0, 1.0));
		//obj.rotate(0.5f, glm::vec3(1.0, 0.0, 0.0));

		camera0.update_model_matrix();
		obj.render(camera0.projectionMatrix, camera0.modelMatrix);

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
					case sf::Key::W:
						kmap.w = true;
						break;
					case sf::Key::S:
						kmap.s = true;
						break;
					case sf::Key::A:
						kmap.a = true;
						break;
					case sf::Key::D:
						kmap.d = true;
						break;
					case sf::Key::L:
						lbool = true;
						break;
					case sf::Key::K:
						kbool = true;
						break;
					case sf::Key::J:
						jbool = true;
						break;
				}
			else if(event.Type == sf::Event::KeyReleased) {
				switch(event.Key.Code) {
					case sf::Key::W:
						kmap.w = false;
						break;
					case sf::Key::S:
						kmap.s = false;
						break;
					case sf::Key::A:
						kmap.a = false;
						break;
					case sf::Key::D:
						kmap.d = false;
						break;
					case sf::Key::L:
						lbool = false;
						break;
					case sf::Key::K:
						kbool = false;
						break;
					case sf::Key::J:
						jbool = false;
						break;
				}
			}
			else if(event.Type == sf::Event::MouseMoved) {
				int dx = window.sf_window.GetInput().GetMouseX() - window.width/2;
				int dy = window.sf_window.GetInput().GetMouseY() - window.height/2;

				camera0.yaw((float)-dx * 0.005);
				camera0.pitch((float)-dy * 0.005);

				window.sf_window.SetCursorPosition(window.width/2, window.height/2);
			}
		}
	}
}

void draw_scene() {
	//obj.render();
}

void load_media() {
	mesh = P3d_load_mesh("examples/monkey.p3d");

	vertex_shd = glCreateShader(GL_VERTEX_SHADER);
	load_shader("examples/shaders/vertex.shd", vertex_shd);
	
	fragment_shd = glCreateShader(GL_FRAGMENT_SHADER);
	load_shader("examples/shaders/fragment.shd", fragment_shd);
}