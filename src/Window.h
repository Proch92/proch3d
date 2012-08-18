class Window {
	public:
		Window();
		Window(int, int);
		Window(int, int, const char*);
		
		void set_width(int);
		void set_height(int);
		void set_window_name(const char*);
		
		void create();
		void resize();
	private:
		int width, height;
		string window_name;
		bool created;
};

#define DEFAULT_SCREEN_WIDTH 800
#define DEFAULT_SCREEN_HEIGHT 600
#define DEFAULT_WINDOW_NAME "proch3d"
#define DEFAULT_WINDOW_X_POS 100
#define DEFAULT_WINDOW_Y_POS 100
