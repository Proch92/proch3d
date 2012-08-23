class P3d_InputManager {
	public:
		P3d_InputManager(sf::Window*);
		
		bool poll_event(sf::Event&);
		
		bool keymap[sizeof(int)];
	private:
		sf::Window* current_window;
};
