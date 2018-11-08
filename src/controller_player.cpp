#include <mode_play.h>
#include "controller_player.h"
#include "Player.h"

void PlayerController::process_input(float delta)
{
	// TODO check that game has started (not in menu)
	Direction dir = NONE;

	int x_dir = 0, y_dir = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))	y_dir++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))	y_dir--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))	x_dir--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))	x_dir++;

	if (x_dir == 1 && y_dir == 1)			dir = NORTHEAST;
	else if (x_dir == 1 && y_dir == 0)		dir = EAST;
	else if (x_dir == 1 && y_dir == -1)		dir = SOUTHEAST;
	else if (x_dir == 0 && y_dir == 1)		dir = NORTH;
	else if (x_dir == 0 && y_dir == -1)		dir = SOUTH;
	else if (x_dir == -1 && y_dir == 1)		dir = NORTHWEST;
	else if (x_dir == -1 && y_dir == 0)		dir = WEST;
	else if (x_dir == -1 && y_dir == -1)	dir = SOUTHWEST;


	// TODO The call to move should probably eventually be handled through the EventManager
	//only call move when necessary
	if (dir != NONE)
	{
		auto mode = std::dynamic_pointer_cast<PlayMode>(state->get_mode());
		auto player = std::static_pointer_cast<Player>(mode->get_level()->get_entities()[0]);
		player->move(dir, delta);
	}
		
}

void PlayerController::handle_event(sf::Event event)
{

}