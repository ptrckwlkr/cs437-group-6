#ifndef CSCI437_PLAYER_CONTROLLER_H
#define CSCI437_PLAYER_CONTROLLER_H

#include "controller.h"
#include "view_player.h"

/**
* Controller class for Stu Dent
*/
class PlayerController : public Controller
{
public:
	PlayerController(GameLogic *state) : Controller(state) {};
	~PlayerController() = default;

	void process_input();
	void handle_event(sf::Event event);
	void set_view_pointer(PlayerView* tmp) { view = tmp; };

private:
	PlayerView* view;
};

#endif //CSCI437_PLAYER_CONTROLLER_H