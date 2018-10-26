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
#include "level_factory.h"

/**
 * Topmost class for the entire game engine, which coordinates the game state with the audio, visuals, and controllers.
 */
class Engine
{
public:
    explicit Engine(sf::RenderWindow *app);
    ~Engine();
    void process_input(float delta);
    void update_state();
    void update_views();
    float clock();

private:
    GameLogic *state;
    EventManager *event_manager;

    std::vector<std::shared_ptr<View>> views;
    std::vector<std::shared_ptr<Controller>> controllers;
    sf::RenderWindow *App;
	sf::View camera;
    sf::Clock time;

};


#endif //CSCI437_ENGINE_H
