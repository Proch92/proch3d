#include "../src/proch3d.h"

void draw_scene();
void load_media();

P3d_Object obj;

P3d_Mesh *mesh;

bool running = true;

int main(int argc, char **argv) {
	P3d_Window window;
	window.create();
	
	P3d_InputManager input_manager(&window.sf_window);
	
	P3d_Renderer renderer;
	renderer.set_current_window(&window.sf_window);
	renderer.set_max_fps(60);
	renderer.show_xyz_axis(true);
	
	P3d_Camera camera0;
	renderer.set_current_camera(&camera0);
	
	load_media();

	obj.set_mesh(mesh);
	
	obj.translate(-2.5, 0.0, -15.0);
	
	sf::Event event;
	
	while(running) {
		
		renderer.clear_screen();
		
		glLoadIdentity();
		
		camera0.camera_glulookat();
		
		draw_scene();

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
	mesh = P3d_load_mesh("examples/prova.obj");
}