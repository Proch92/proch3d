#include "src/proch3d.h"

void draw_scene();

P3d_Object cube;
P3d_Object cube2;

bool running = true;

int main(int argc, char **argv) {
	P3d_Window window;
	window.create();
	
	P3d_InputManager input_manager(&window.sf_window);
	
	P3d_Renderer renderer;
	renderer.set_current_window(&window.sf_window);
	renderer.set_draw_scene_function(draw_scene);
	renderer.set_max_fps(60);
	
	P3d_Camera camera0;
	renderer.set_current_camera(&camera0);
	
	cube.translate(-2.5, 0.0, -15.0);
	cube2.translate(2.5, 0.0, -15.0);
	
	cube2.set_color(P3d_Color4f(0.5, 0.5, 1.0, 0.0));
	
	sf::Event event;
	
	while(running) {
		cube.translate(0.0, 0.05, 0.0);
		cube.rotate(0.0, 0.5, 0.0);
		
		cube2.translate(0.02, -0.03, -0.07);
		cube2.rotate(0.2, 0.5, 0.6);
		
		camera0.translate(0.0, 0.0, 0.05);
		camera0.rotate(0.0, 0.05, 0.0);
		
		renderer.render();
		
		while(input_manager.poll_event(event)) {
			if(event.Type == sf::Event::KeyPressed)
				if(event.Key.Code == sf::Key::Escape) running = false;
				else printf("%c\n", event.Text.Unicode);
		}
	}
}

void draw_scene() {
	cube.render();
	cube2.render();
}
