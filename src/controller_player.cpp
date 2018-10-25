#include "controller_player.h"
#include "macros.h"

void PlayerController::process_input()
{
	// TODO check that game has started (not in menu)

	sf::Vector2f pos = view->get_coords();
	float delta_x = 0, delta_y = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		delta_y -= PLAYER_SPEED;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		delta_y += PLAYER_SPEED;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		delta_x -= PLAYER_SPEED;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		delta_x += PLAYER_SPEED;

	if (delta_x != 0 || delta_y != 0)
		view->set_coords(pos.x + delta_x, pos.y + delta_y);
}

void PlayerController::handle_event(sf::Event event)
{

}