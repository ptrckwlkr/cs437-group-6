#ifndef CSCI437_PLAYER_VIEW_LOST_H
#define CSCI437_PLAYER_VIEW_LOST_H


#include "player_view.h"
#include "macros.h"

class LostView : public PlayerView
{

private:
    void process_input(float delta) override;
    void handle_event(sf::Event event) override;
    int selectionIndex;	//represents current highlighted option on screen

public:
    LostView(GameLogic *state, sf::RenderWindow *App);
    void update(float delta) override;
    void draw(float delta) override;

};


#endif //CSCI437_PLAYER_VIEW_LOST_H
