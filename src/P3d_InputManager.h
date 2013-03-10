class P3d_InputManager {
	public:
		P3d_InputManager(sf::RenderWindow*);
		
		bool poll_event(sf::Event&);
		
		bool is_key_down(sf::Key::Code);
	private:
		sf::RenderWindow* current_window;
};
