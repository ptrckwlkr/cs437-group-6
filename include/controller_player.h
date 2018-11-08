#ifndef CSCI437_PLAYER_CONTROLLER_H
#define CSCI437_PLAYER_CONTROLLER_H

#include "controller.h"

/**
* Controller class for Stu Dent
*/
class PlayerController : public Controller
{
public:
	PlayerController(GameLogic *state) : Controller(state) {};
	~PlayerController() = default;

	void process_input(float delta, sf::Vector2f mouse_pos);
	void handle_event(sf::Event event);

private:
};

#endif //CSCI437_PLAYER_CONTROLLER_H
