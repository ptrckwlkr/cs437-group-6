#include "controller_menu.h"
#include "mode_menu.h"
#include <iostream>
#include "macros.h"

void MenuController::process_input(float delta, sf::Vector2f mouse_pos)
{
	//avoids crashes when state has changed
	if (state->has_mode_changed()) return;

	//gets mode object
	//ensures menu mode selection index is within proper range
	auto mode = std::dynamic_pointer_cast<MenuMode>(state->get_mode());

	if ((*mode).screenIndex == 0 && (WINDOW_WIDTH / 6.f) < mouse_pos.x  && mouse_pos.x < (5 * WINDOW_WIDTH / 6.f))
	{
		if (275 < mouse_pos.y && mouse_pos.y <= 325)
			(*mode).selectionIndex = 0;
		else if (325 < mouse_pos.y && mouse_pos.y <= 375)
			(*mode).selectionIndex = 1;
		else if (375 < mouse_pos.y && mouse_pos.y <= 425)
			(*mode).selectionIndex = 2;
	}
}


void MenuController::handle_event(sf::Event event)
{
	//gets mode object
	//ensures menu mode selection index is within proper range
	auto mode = std::dynamic_pointer_cast<MenuMode>(state->get_mode());


	/*since this function is called inside the poll event loop, there is an OS delay which produces the
	desired cursor movement on the menu*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		(*mode).selectionIndex = ((*mode).selectionIndex + NUM_MENU_BUTTONS - 1) % NUM_MENU_BUTTONS;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		(*mode).selectionIndex = ((*mode).selectionIndex + 1) % NUM_MENU_BUTTONS;


	//KeyReleased so that the next screen doesn't immediately think confirm has been hit 
	if ((event.key.code == sf::Keyboard::E && event.type == sf::Event::KeyReleased) ||
		(event.key.code == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased))
	{
		//changes the game mode when player selects play
		if (mode->makeSelection())
			state->set_mode(GameMode(MODE_PLAY));	//TODO this should probably be changed to level select
	}
		

	if ((event.key.code == sf::Keyboard::Q && event.type == sf::Event::KeyReleased) || 
		(event.key.code == sf::Mouse::Right && event.type == sf::Event::MouseButtonReleased))
		mode->goBack();

}