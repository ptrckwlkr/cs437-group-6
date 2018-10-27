#include <SFML/Window/Event.hpp>
#include <chrono>
#include <view_example.h>
#include <level_factory.h>
#include <controller_example.h>
#include "engine.h"
#include "macros.h"


Engine::Engine(sf::RenderWindow *app) : App(app)
{
  // Load fonts and audio
  // Initialize game state, graphics, sound, and controllers here
  state = new GameLogic();
  // event_manager = new EventManager(); TODO

  controllers.push_back(std::make_shared<ExampleController>(state));
  views.push_back(std::make_shared<ExampleView>(state));

  time = std::chrono::steady_clock::now();
};

Engine::~Engine()
{
  delete state;
}

/**
 * Process all events, automatic updates, and keyboard input for all controllers.
 */
void Engine::process_input()
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
    c->process_input();
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
void Engine::clock()
{
  std::chrono::steady_clock::time_point temp = std::chrono::steady_clock::now();
  double interval = std::chrono::duration_cast<std::chrono::milliseconds>(temp - time).count();
  g_time_elapsed = interval / 1000 * GAME_CLOCK_SCALER;
  time = std::chrono::steady_clock::now();
}


