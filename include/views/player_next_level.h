#ifndef CSCI437_PLAYER_NEXT_LEVEL_H
#define CSCI437_PLAYER_NEXT_LEVEL_H


#include "game_logic.h"
#include "player_view.h"

class NextLevelView : public PlayerView
{

private:
    void process_input(float delta) override;
    void handle_event(sf::Event event) override;
    int selectionIndex;	//represents current highlighted option on screen

public:
    NextLevelView(GameLogic *state, sf::RenderWindow *App);
    void update(float delta) override;
    void draw(float delta) override;

};

#endif //CSCI437_PLAYER_NEXT_LEVEL_H
