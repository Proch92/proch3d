#include "proch3d.h"

/*P3d_InputManager::P3d_InputManager(sf::Window *cw) {
	current_window = cw;
	//input = current_window->GetInput();
}*/

P3d_InputManager::P3d_InputManager(sf::RenderWindow *cw) {
	current_window = cw;
	//input = current_window->GetInput();
}

bool P3d_InputManager::poll_event(sf::Event &event) {
	bool returning = current_window->GetEvent(event);
	
	if(returning) {
		/*if(event.Type == sf::Event::KeyPressed)
			keymap[event.Key.Code] = true;
		else if(event.Type == sf::Event::KeyReleased)
			keymap[event.Key.Code] = false;
		else */if(event.Type == sf::Event::MouseMoved) {
			current_window->SetCursorPosition(current_window->GetWidth() / 2, current_window->GetHeight() / 2);
			
			event.MouseMove.X = (current_window->GetWidth() / 2) - event.MouseMove.X;
			event.MouseMove.Y = (current_window->GetHeight() / 2) - event.MouseMove.Y;
		}
	}
	
	return returning;
}

bool P3d_InputManager::is_key_down(sf::Key::Code code) {
	const sf::Input& input = current_window->GetInput();
	
	return input.IsKeyDown(code);
}
