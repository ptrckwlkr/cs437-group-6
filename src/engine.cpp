#include <SFML/Window/Event.hpp>
#include <chrono>
#include <view_example.h>
#include <view_player.h>
#include <level_factory.h>
#include <controller_example.h>
#include <controller_player.h>
#include <mode_play.h>
#include "engine.h"
#include "macros.h"
#include "ResourceManager.h"
#include <iostream>


Engine::Engine(sf::RenderWindow *app) : App(app)
{
  // Load fonts and audio
  // Initialize game state, graphics, sound, and controllers here
  state = new GameLogic();
  // event_manager = new EventManager(); TODO

  //loads necessary resources to the resource manager
  resources.LoadFont("old_school", "../data/Old-School-Adventures.ttf");
  resources.LoadXML("text", "../data/game-text.xml");

  //controllers.push_back(std::make_shared<PlayerController>(state));
  //views.push_back(std::make_shared<PlayerView>(state));

  //menuController = std::make_shared<MenuController>(state);
  //menuView = std::make_shared<MenuView>(state);
  controllers.push_back(std::make_shared<MenuController>(state));
  views.push_back(std::make_shared<MenuView>(state));



  // initiliazes the camera
  camera.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

  //starts clock
  time.restart();
};

Engine::~Engine()
{
  delete state;
}

/**
 * Process all events, automatic updates, and keyboard input for all controllers.
 */
void Engine::process_input(float delta)
{
  // Process events
  sf::Event event;
  while (App->pollEvent(event))
  {
    for (const auto &c : controllers)
    {
      c->handle_event(event);
    }

    if (event.type == sf::Event::Closed) App->close();
  }

  // Process input
  for (const auto &c : controllers)
  {
    c->process_input(delta);
  }

  // Listen for shutdown signal
  if (state->shutdown()) App->close();
}

/**
 * Update the game state.
 */
void Engine::update_state()
{
  if (!state->is_paused()) state->update_state();
}

/**
 * Update the sound and graphics.
 */
void Engine::update_views()
{
// centers view on player and clears window
  //auto mode = std::dynamic_pointer_cast<PlayMode>(state->get_mode());
  //Position playerPos = mode->get_level()->get_entities()[0]->get_position();
  //camera.setCenter(playerPos.x * GRAPHICS_SCALER, playerPos.y * GRAPHICS_SCALER);
  //App->setView(camera);
  App->clear(sf::Color::Black);

  for (const auto &v : views)
  {
    App->draw(*v);
  }

  App->display();
}

/**
 * Update elapsed time to regulate main game loop.
 */
float Engine::clock()
{
	return time.restart().asSeconds() * GAME_CLOCK_SCALER;
}


