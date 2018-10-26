#include "controller_player.h"
#include "macros.h"

void PlayerController::process_input(float delta)
{
	// TODO check that game has started (not in menu)
	Position pos = state->get_level()->get_entities()[0]->get_position();
	float delta_x = 0, delta_y = 0;

	//looks at keyboard state and updates coordinates appropriately
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))	delta_y -= PLAYER_SPEED * delta;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))	delta_y += PLAYER_SPEED * delta;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	delta_x -= PLAYER_SPEED * delta;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))	delta_x += PLAYER_SPEED * delta;
	//only update when necessary
	if (delta_x != 0 || delta_y != 0)
		state->get_level()->get_entities()[0]->set_position(pos.x + delta_x, pos.y + delta_y);
}

void PlayerController::handle_event(sf::Event event)
{

}