#ifndef CSCI437_CONTROLLER_MENU_H
#define CSCI437_CONTROLLER_MENU_H

#include "controller.h"

class MenuController : public Controller
{

public:
	MenuController(GameLogic *state) : Controller(state) {};
	~MenuController() = default;
	void process_input(float delta);
	void handle_event(sf::Event event);

private:


};


#endif //CSCI437_CONTROLLER_MENU_H
