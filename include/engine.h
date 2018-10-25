#ifndef CSCI437_ENGINE_H
#define CSCI437_ENGINE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include "game_logic.h"
#include "controller.h"
#include "view.h"
#include "EventManager.h"
#include "level.h"

/**
 * Topmost class for the entire game engine, which coordinates the game state with the audio, visuals, and controllers.
 */
class Engine
{
public:
    explicit Engine(sf::RenderWindow *app);
    ~Engine();
    void process_input();
    void update_state();
    void update_views();
    void clock();

private:
    GameLogic *state;
    std::vector<std::shared_ptr<View>> views;
    std::vector<std::shared_ptr<Controller>> controllers;
    sf::RenderWindow *App;
    std::chrono::steady_clock::time_point time;
    std::shared_ptr<EventManager> event_manager;

    std::shared_ptr<Level> curr_level;
};


#endif //CSCI437_ENGINE_H
