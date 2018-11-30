#ifndef CSCI437_VIEW_GAME_H
#define CSCI437_VIEW_GAME_H

#include <SFML/Audio.hpp>
#include <memory>
#include "player_view.h"

/**
* Controller class for Stu Dent
*/
class GameView : public PlayerView
{

public:
    GameView(GameLogic *state, sf::RenderWindow *App);
    ~GameView();
    void update(float delta) override;
    void draw() override;
    //to be used to update sprite movement 
    Animation animation_player;
    Animation animation_skeleton;

    bool getMapMode() {return map_mode;}

private:
    void process_input(float delta) override;
    void handle_event(sf::Event event) override;
    sf::Texture skeleton_text;
    sf::Texture player_text;
    std::shared_ptr<sf::Music> bg_music;

    bool map_mode;

};

#endif //CSCI437_VIEW_GAME_H
