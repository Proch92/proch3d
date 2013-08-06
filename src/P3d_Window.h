class P3d_Window {
	public:
		P3d_Window();
		P3d_Window(int, int);
		P3d_Window(int, int, const char*);
		
		void set_width(int);
		void set_height(int);
		void set_window_name(const char*);
		
		string& get_name();
		
		void create();
		void resize();
		
		//sf::Window sf_window;
		sf::RenderWindow sf_window;
		int width, height;
	private:
		string window_name;
		bool created;
};

#define DEFAULT_SCREEN_WIDTH 1920
#define DEFAULT_SCREEN_HEIGHT 1080
#define DEFAULT_WINDOW_NAME "proch3d"
#define DEFAULT_WINDOW_X_POS 100
#define DEFAULT_WINDOW_Y_POS 100
