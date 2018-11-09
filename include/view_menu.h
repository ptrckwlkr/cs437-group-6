#ifndef CSCI437_CONTROLLER_MENU_H
#define CSCI437_CONTROLLER_MENU_H

#include "view.h"

class MenuView : public PlayerView
{

public:
	MenuView(GameLogic *state, sf::RenderWindow *App) : PlayerView(state, App) {};
	~MenuView() = default;
	void process_input(float delta, sf::Vector2f mouse_pos);
	void handle_event(sf::Event event);
  void update(float delta);
	void draw();

	int selectionIndex;	//represents current highlighted option on screen
	int screenIndex;	//represents current menu screen to display
	bool makeSelection();
	void goBack();

private:



};


#endif //CSCI437_CONTROLLER_MENU_H
