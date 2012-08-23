//#define MAX_CAMERAS_ON_STAGE 10

class P3d_Renderer {
	public:
		P3d_Renderer();
		void render();
		void set_inrender_function(void (*foo) ());
		void set_draw_scene_function(void (*foo) ());
		void set_clear_color(float, float, float, float);
		void set_max_fps(int);
		void set_current_camera(P3d_Camera*);
		void set_current_window(sf::Window*);
	private:
		void (*inrender_function) ();
		void (*draw_scene) ();
		
		P3d_Camera *current_camera;
		sf::Window *current_window;
		
		P3d_Timer fps_timer;
		int fps;
		
		int max_fps;
};
