#ifndef CSCI437_VIEW_GAME_H
#define CSCI437_VIEW_GAME_H

#include "view.h"
#include "player_view.h"

/**
* Controller class for Stu Dent
*/
class GameView : public PlayerView
{

public:
    GameView(GameLogic *state, sf::RenderWindow *App);
    void update(float delta) override;
    void draw() override;
    //to be used to update sprite movement 
    Animation animation_player;
    Animation animation_skeleton;

private:
    void process_input(float delta) override;
    void handle_event(sf::Event event) override;
    sf::Texture skeleton_text;
    sf::Texture player_text;

};

#endif //CSCI437_VIEW_GAME_H
