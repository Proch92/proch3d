//#define MAX_CAMERAS_ON_STAGE 10

class Renderer {
	public:
		Renderer();
		void render();
		void set_inrender_function(void (*foo) ());
		void set_draw_scene_function(void (*foo) ());
		void set_clear_color(float, float, float, float);
		void set_max_fps(int);
		void set_current_camera(Camera*);
	private:
		void (*inrender_function) ();
		void (*draw_scene) ();
		
		Camera *current_camera;
		
		Timer fps_timer;
		int fps;
		
		int max_fps;
};
