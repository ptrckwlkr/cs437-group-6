#ifndef CSCI437_ENGINE_H
#define CSCI437_ENGINE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include "game_logic.h"
#include "view.h"
#include "ResourceManager.h"


enum GameMode
{
		MODE_MENU,
		MODE_LEVEL_SELECT,
		MODE_SHOP,
		MODE_PLAY,
};

/**
 * Topmost class for the entire game engine, which coordinates the game state with the audio, visuals, and controllers.
 */
class Engine
{
public:
    static Engine* GameEngine();
    void init(sf::RenderWindow *app);
		void update_views(float delta);
    void update_state(float delta);
		void update_graphics();
    void set_mode(GameMode mode);
    float clock();
	

private:
    Engine();
    ~Engine();
    void switch_mode();

    GameLogic *state;
    sf::RenderWindow *App;
    sf::Clock time;

    std::vector<std::shared_ptr<View>> views;
    std::shared_ptr<PlayerView> curr_player_view;
		GameMode curr_game_mode;
};

//global access to resource manager
extern ResourceManager resources;


#endif //CSCI437_ENGINE_H
