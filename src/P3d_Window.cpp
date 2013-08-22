#include "proch3d.h"

P3d_Window::P3d_Window() {
	created = false;
	
	width = DEFAULT_SCREEN_WIDTH;
	height = DEFAULT_SCREEN_HEIGHT;
	window_name = DEFAULT_WINDOW_NAME;
}

P3d_Window::P3d_Window(int w, int h) {
	created = false;
	
	width = w;
	height = h;
	window_name = DEFAULT_WINDOW_NAME;
}

P3d_Window::P3d_Window(int w, int h, const char* w_name) {
	created = false;
	
	width = w;
	height = h;
	window_name = w_name;
}



void P3d_Window::create() {
	sf_window.Create(sf::VideoMode(width, height, 32), window_name/*, sf::Style::Fullscreen*/);
	sf_window.SetCursorPosition(width/2, height/2);
	sf_window.ShowMouseCursor(false);
	resize();
	
	created = true;
}

void P3d_Window::resize() {
	if(created)
		sf_window.Create(sf::VideoMode(width, height, 32), window_name/*, sf::Style::Fullscreen*/);
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}


//utils -------------------------------------------------------------------------------
void P3d_Window::set_width(int value) {
	width = value;
	
	if(created)
		resize();
}

void P3d_Window::set_height(int value) {
	height = value;
	
	if(created)
		resize();
}

void P3d_Window::set_window_name(const char* w_name) {
	window_name = w_name;
	
	if(created)
		resize();
}

string& P3d_Window::get_name() {
	return window_name;
}
