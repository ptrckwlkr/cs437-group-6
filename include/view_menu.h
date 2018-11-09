#ifndef CSCI437_VIEW_MENU_H
#define CSCI437_VIEW_MENU_H

#include "view.h"

class MenuView : public PlayerView
{

public:
    MenuView(GameLogic *state, sf::RenderWindow *App);
    void update(float delta) override;
    void draw() override;
    int selectionIndex;	//represents current highlighted option on screen
    int screenIndex;	//represents current menu screen to display

private:
    void process_input(float delta) override;
    void handle_event(sf::Event event) override;
		bool makeSelection();
		void goBack();

};


#endif //CSCI437_VIEW_MENU_H
