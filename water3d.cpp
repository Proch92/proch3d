#include "src/proch3d.h"

void draw_scene();

bool running = true;

Water water(100, 100);

int main(int argc, char **argv) {
	srand(time(NULL));
	
	P3d_Window window;
	window.create();
	
	P3d_InputManager input_manager(&window.sf_window);
	
	P3d_Renderer renderer;
	renderer.set_current_window(&window.sf_window);
	renderer.set_draw_scene_function(draw_scene);
	renderer.set_max_fps(60);
	
	P3d_Camera camera0;
	renderer.set_current_camera(&camera0);
	
	sf::Event event;
	
	camera0.move(P3d_Vector3f(35, 25, 60));
	camera0.rotate(-30, 10, 0);
	
	//water.giveInput(5, 5, 5);
	
	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_DEPTH_TEST);
	
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT2, GL_POSITION, light_position);
	
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);*/
	
	while(running) {
		renderer.render();
		
		while(input_manager.poll_event(event)) {
			if (event.Type == sf::Event::Closed)
				running = false;
			else if(event.Type == sf::Event::KeyPressed)
				switch(event.Key.Code) {
					case sf::Key::Escape:
						running = false;
						break;
				}
			else if(event.Type == sf::Event::MouseButtonPressed)
				water.giveInput(rand()%(water.dimx-2) + 1, rand()%(water.dimy-2) + 1, (rand()%2)?1:-1);
		}
		
		water.compute();
	}
}

void draw_scene() {
	water.show();
}
