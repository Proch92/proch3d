#include "proch3d.h"

Window::Window() {
	created = false;
	
	width = DEFAULT_SCREEN_WIDTH;
	height = DEFAULT_SCREEN_HEIGHT;
	window_name = DEFAULT_WINDOW_NAME;
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(DEFAULT_WINDOW_X_POS, DEFAULT_WINDOW_Y_POS);
	glutInitWindowSize(width, height);
}

Window::Window(int w, int h) {
	created = false;
	
	width = w;
	height = h;
	window_name = DEFAULT_WINDOW_NAME;
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(DEFAULT_WINDOW_X_POS, DEFAULT_WINDOW_Y_POS);
	glutInitWindowSize(width, height);
}

Window::Window(int w, int h, const char* w_name) {
	created = false;
	
	width = w;
	height = h;
	window_name = w_name;
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(DEFAULT_WINDOW_X_POS, DEFAULT_WINDOW_Y_POS);
	glutInitWindowSize(width, height);
}



void Window::create() {
	created = true;
	
	glutCreateWindow(window_name.c_str());
	resize();
}

void Window::resize() {
	if(created)
		glutReshapeWindow(width, height);
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); 
}


//utils -------------------------------------------------------------------------------
void Window::set_width(int value) {
	width = value;
	
	if(created)
		resize();
}

void Window::set_height(int value) {
	height = value;
	
	if(created)
		resize();
}

void Window::set_window_name(const char* w_name) {
	window_name = w_name;
	
	if(created)
		glutSetWindowTitle(window_name.c_str());
}
