#ifndef CSCI437_ENGINE_H
#define CSCI437_ENGINE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include "game_logic.h"
#include "view.h"
#include "graphics.h"
#include "EventManager.h"
#include "level.h"
#include "level_factory.h"
#include "ResourceManager.h"
#include "graphics_menu.h"
#include "view_menu.h"


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
    explicit Engine(sf::RenderWindow *app);
    ~Engine();
		void update_views(float delta);
    void update_state(float delta);
		void update_graphics();
    float clock();
	

private:
		void switch_mode();
    GameLogic *state;
    EventManager *event_manager;

    sf::RenderWindow *App;
    sf::Clock time;

    std::vector<std::shared_ptr<View>> views;
    std::shared_ptr<PlayerView> curr_player_view;
		GameMode curr_game_mode;

};

//global access to resource manager
extern ResourceManager resources;


#endif //CSCI437_ENGINE_H
