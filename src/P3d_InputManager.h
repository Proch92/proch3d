struct MousePosition {
	int x;
	int y;
	float last_dx;
	float last_dy;
};

class P3d_InputManager {
	public:
		//P3d_InputManager(sf::Window*);
		P3d_InputManager(sf::RenderWindow*);
		
		bool poll_event(sf::Event&);
		
		bool is_key_down(sf::Key::Code);
		
		//sf::Input& input;
		//bool keymap[sizeof(int)];
		struct MousePosition mouse_position;
	private:
		//sf::Window* current_window;
		sf::RenderWindow* current_window;
};
