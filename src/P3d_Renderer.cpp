#include "proch3d.h"

P3d_Renderer::P3d_Renderer() {
	inrender_function = NULL;
	draw_scene = NULL;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	
	glMatrixMode(GL_MODELVIEW);
	
	glClearColor(1.0, 1.0, 1.0, 0.0); //default
	
	current_camera = NULL;
	current_window = NULL;
	
	fps_timer.start();
	fps = 0;
	max_fps = 0;
	
	showing_axis = false;
}


void P3d_Renderer::render() {
	if(inrender_function != NULL) inrender_function();
	if(current_camera == NULL) return;
	
	//clean the screen
	glClear(GL_COLOR_BUFFER_BIT);
	
	//orient camera
	glLoadIdentity();
	current_camera->camera_glulookat();
	
	//show axis for debug
	if(showing_axis)
		show_axis();
	
	//draw text
	//show_debug_text(string("test"), 10, 10);
	
	//draw things
	if(draw_scene != NULL)
		draw_scene();
	
	//update screen
	if(current_window != NULL)
		current_window->Display();
	
	//fps
	if(max_fps != 0 && fps_timer.get_elapsed_last_call() <= (1000/max_fps)) {
		p3d_delay(1000/max_fps);
	}
	if(fps_timer.get_tick() >= 1000) {
		printf("fps = %d\n", fps);
		fps = 0;
		fps_timer.start();
	}
	else fps++;
}


void P3d_Renderer::set_inrender_function(void (*foo) ()) {
	inrender_function = foo;
}

void P3d_Renderer::set_draw_scene_function(void (*foo) ()) {
	draw_scene = foo;
}

void P3d_Renderer::set_clear_color(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
}

void P3d_Renderer::set_current_camera(P3d_Camera *ptr) {
	current_camera = ptr;
}

void P3d_Renderer::set_max_fps(int mfps) {
	max_fps = mfps;
}

/*void P3d_Renderer::set_current_window(sf::Window* w) {
	current_window = w;
}*/

void P3d_Renderer::set_current_window(sf::RenderWindow* w) {
	current_window = w;
}

void P3d_Renderer::show_xyz_axis(bool value) {
	showing_axis = value;
}

void P3d_Renderer::show_axis() {
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glBegin(GL_LINE);
		glVertex3f(-10.0, 0.0, 0.0);
		glVertex3f(10.0, 0.0, 0.0);
	glEnd();
	
	glColor4f(0.0, 1.0, 0.0, 1.0);
	glBegin(GL_LINE);
		glVertex3f(0.0, 0.0, -10.0);
		glVertex3f(0.0, 0.0, 10.0);
	glEnd();
	
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glBegin(GL_LINE);
		glVertex3f(0.0, -10.0, 0.0);
		glVertex3f(0.0, 10.0, 0.0);
	glEnd();
}

void P3d_Renderer::show_debug_text(string message, int x, int y) {
	/*sf::String msg;
	msg.SetText(message.c_str());
	msg.SetFont(sf::Font::GetDefaultFont());
	msg.SetSize(DEBUG_TEXT_SIZE);
	msg.Move((float) x, (float) y);
	msg.SetColor(sf::Color(128, 128, 128));
	current_window->Draw(msg);*/
}
