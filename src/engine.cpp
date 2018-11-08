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

  // initializes the camera
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

  //process events
  EventManager::Instance()->ProcessEvents;

  // Listen for shutdown signal
  if (state->shutdown()) App->close();
}

/**
 * Update the game state.
 */
void Engine::update_state()
{
  /*ensures that the vectors of controllers and views reflect current game mode

  NOTE: this is placed in this method because if it is within a method that references controllers or 
  views, after the vectors are changed and change_mode() returns, there will be copies of the original
  vectors in the method that called change_mode().*/
  if (state->has_mode_changed())
	change_mode();

  if (!state->is_paused()) state->update_state();
}

/**
 * Update the sound and graphics.
 */
void Engine::update_views()
{
	// centers view on player while game is in play
  if (state->get_gameMode() == GameMode::MODE_PLAY)
  {
	auto mode = std::dynamic_pointer_cast<PlayMode>(state->get_mode());
	Position playerPos = mode->get_level()->get_entities()[0]->get_position();
	camera.setCenter(playerPos.x * GRAPHICS_SCALER, playerPos.y * GRAPHICS_SCALER);
	App->setView(camera);
  }

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


/*
	Maintains the vectors storing Views and Controllers, adds/removes mode specific views/controllers
	when the game mode is changed.
*/
void Engine::change_mode()
{
	//vectors are emptied upon change of mode
	controllers.clear();
	views.clear();

	//places the primary controller and view for the mode at the 0th index of each vector
	switch (state->get_gameMode())
	{
	case GameMode::MODE_MENU:
		controllers.push_back(std::make_shared<MenuController>(state));
		views.push_back(std::make_shared<MenuView>(state));
		break;
	case GameMode::MODE_PLAY:
		controllers.push_back(std::make_shared<PlayerController>(state));
		views.push_back(std::make_shared<PlayerView>(state));
		break;
	case GameMode::MODE_MAP:
		break;
	case GameMode::MODE_SHOP:
		break;
	}
	
	state->finished_mode_change();
}
