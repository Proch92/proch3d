#include "proch3d.h"

P3d_InputManager::P3d_InputManager(sf::RenderWindow *cw) {
	current_window = cw;
}

bool P3d_InputManager::poll_event(sf::Event &event) {
	bool returning = current_window->GetEvent(event);
	
	return returning;
}

bool P3d_InputManager::is_key_down(sf::Key::Code code) {
	const sf::Input& input = current_window->GetInput();
	
	return input.IsKeyDown(code);
}
