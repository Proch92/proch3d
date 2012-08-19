#include "proch3d.h"

Renderer::Renderer() {
	inrender_function = NULL;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	
	glMatrixMode(GL_MODELVIEW);
	
	glClearColor(1.0, 1.0, 1.0, 0.0); //default
	
	current_camera = NULL;
}


void Renderer::render() {
	if(inrender_function != NULL) inrender_function();
	if(current_camera == NULL) return;
	
	//clean the screen
	glClear(GL_COLOR_BUFFER_BIT);
	
	//orient camera
	glLoadIdentity();
	current_camera->camera_glulookat();
	
	//draw things
	glColor3f(1.0, 0.0, 0.0);
	 
	glutWireCube(5.0); // Box.
	
	//update screen
	glFlush();
}


void Renderer::set_inrender_function(void (*foo) ()) {
	inrender_function = foo;
}

void Renderer::set_clear_color(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

void Renderer::set_current_camera(Camera *ptr) {
	current_camera = ptr;
}
