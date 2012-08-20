#include "src/proch3d.h"
#include "stdio.h"

void draw_scene();

Object cube;

int main(int argc, char **argv) {
	Core core(&argc, argv);
	Window window;	
	window.create();
	
	Renderer renderer;
	renderer.set_draw_scene_function(draw_scene);
	
	Camera camera0;
	renderer.set_current_camera(&camera0);
	
	//camera0.translate(0.0, 0.0, 15.0);
	
	cube.translate(0.0, 0.0, -15.0);
	
	int i;
	for(i=0; i!=1000; i++) {
		system("sleep 0.01");
		
		cube.translate(0.0, 0.02, 0.0);
		cube.rotate(0.0, 0.0, 0.5);
		
		//camera0.translate(0.02, 0.0, 0.04);
		//camera0.rotate(0.0, 1.0, 0.0);
		
		renderer.render();
	}
}

void draw_scene() {
	cube.render();
}
