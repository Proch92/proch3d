#include "src/proch3d.h"

void draw_scene();

P3d_Object cube;
P3d_Object cube2;
P3d_Object base;

bool running = true;

int main(int argc, char **argv) {
	P3d_Window window;
	window.create();
	
	P3d_InputManager input_manager(&window.sf_window);
	
	P3d_Renderer renderer;
	renderer.set_current_window(&window.sf_window);
	renderer.set_draw_scene_function(draw_scene);
	renderer.set_max_fps(60);
	renderer.show_xyz_axis(true);
	
	P3d_Camera camera0;
	renderer.set_current_camera(&camera0);
	
	cube.translate(-2.5, 0.0, -15.0);
	cube2.translate(2.5, 0.0, -15.0);
	base.translate(0, -10, 0);
	base.rotate(90, 0, 0);
	
	cube2.set_color(P3d_Color4f(0.5, 0.5, 1.0, 0.0));
	
	sf::Event event;
	
	while(running) {
		/*cube.translate(0.0, 0.05, 0.0);
		cube.rotate(0.0, 0.5, 0.0);
		
		cube2.translate(0.02, -0.03, -0.07);
		cube2.rotate(0.2, 0.5, 0.6);
		
		camera0.translate(0.0, 0.0, 0.05);
		camera0.rotate(0.0, 0.05, 0.0);*/
		
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
			else if(event.Type == sf::Event::MouseMoved)
				camera0.rotate(((float)event.MouseMove.Y) / 20, ((float)event.MouseMove.X) / 20, 0.0);
		}
		
		if(input_manager.is_key_down(sf::Key::A))
			camera0.move(P3d_Vector3f(-1.0, 0.0, 0.0));
		if(input_manager.is_key_down(sf::Key::D))
			camera0.move(P3d_Vector3f(1.0, 0.0, 0.0));
		if(input_manager.is_key_down(sf::Key::S))
			camera0.move(P3d_Vector3f(0.0, 0.0, -1.0));
		if(input_manager.is_key_down(sf::Key::W))
			camera0.move(P3d_Vector3f(0.0, 0.0, 1.0));
		
		//debug
		/*P3d_Vector4f &orient = camera0.get_orient();
		stringstream orientx;
		orientx << orient[0];
		stringstream orienty;
		orienty << orient[1];
		stringstream orientz;
		orientz << orient[2];*/
		//renderer.show_debug_text(string("orient: ") + orientx.str() + string(" ") + orienty.str() + string(" ") + orientz.str(), 10, 10);
	}
}

void draw_scene() {
	cube.render();
	cube2.render();
	base.render();
}
