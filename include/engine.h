#ifndef CSCI437_ENGINE_H
#define CSCI437_ENGINE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include "game_logic.h"
#include "ResourceManager.h"
#include "MusicManager.h"
#include "sound_manager.h"
#include "GearSet.h"

enum GameMode
{
		MODE_MENU,
		MODE_LEVEL_SELECT,
		MODE_SHOP,
		MODE_PLAY,
		MODE_VICTORY,
		MODE_INVENTORY,
};

/**
 * Topmost class for the entire game engine, which coordinates the game state with the audio, visuals, and controllers.
 */
class Engine
{
public:
    static Engine &getInstance();
    void init(sf::RenderWindow *app);
		void update_views(float delta);
    void update_state(float delta);
		void update_graphics(float delta);
    void set_mode(GameMode mode);
		void start_new_game(int level);
		void shutdown();
    float clock();
	

private:
    Engine() = default;
    ~Engine() = default;
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;
    void switch_mode();

    GameLogic state;
    sf::RenderWindow *App;
    sf::Clock time;
    GameMode curr_game_mode;
    SoundManager soundmanager = SoundManager();
};

//global access to resource manager
extern ResourceManager resources;

#endif //CSCI437_ENGINE_H
