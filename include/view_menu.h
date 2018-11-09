#ifndef CSCI437_CONTROLLER_MENU_H
#define CSCI437_CONTROLLER_MENU_H

#include "graphics_menu.h"
#include "view.h"

class MenuView : public PlayerView
{

public:
    MenuView(GameLogic *state, sf::RenderWindow *App);;
    ~MenuView() = default;
    void update(float delta) override;
    void draw() override;
    int selectionIndex;	//represents current highlighted option on screen
    int screenIndex;	//represents current menu screen to display

private:
    void process_input(float delta);
    void handle_event(sf::Event event);
		bool makeSelection();
		void goBack();
    MenuGraphics *graphics;

};


#endif //CSCI437_CONTROLLER_MENU_H
