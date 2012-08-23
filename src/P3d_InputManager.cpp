#include "proch3d.h"

P3d_InputManager::P3d_InputManager(sf::Window *cw) {
	int i;
	for(i=0; i!=sizeof(int); i++)
		keymap[i] = false;
	
	current_window = cw;
}

bool P3d_InputManager::poll_event(sf::Event &event) {
	bool returning = current_window->GetEvent(event);
	
	if(returning) {
		if(event.Type == sf::Event::KeyPressed)
			keymap[event.Text.Unicode] = true;
		else if(event.Type == sf::Event::KeyReleased)
			keymap[event.Text.Unicode] = false;
	}
	
	return returning;
}
