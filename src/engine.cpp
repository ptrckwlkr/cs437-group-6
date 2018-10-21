#include <SFML/Window/Event.hpp>
#include <chrono>
#include "engine.h"
#include "macros.h"


Engine::Engine(sf::RenderWindow *app) : App(app)
{
  // Load fonts and audio
  // Initialize game state, graphics, sound, and controllers here

  time = std::chrono::steady_clock::now();
};

Engine::~Engine()
{

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
    for (auto c : controllers)
    {
      c->handle_event(event);
    }

    if (event.type == sf::Event::Closed) App->close();
  }

  // Process input
  for (auto c : controllers)
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


