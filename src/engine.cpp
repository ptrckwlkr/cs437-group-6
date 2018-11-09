#include <SFML/Window/Event.hpp>
#include <iostream>
#include <chrono>
#include "graphics_example.h"
#include "graphics_game.h"
#include "view_game.h"
#include "engine.h"
#include "macros.h"
#include "ResourceManager.h"



Engine::Engine(sf::RenderWindow *app) : App(app)
{
  curr_game_mode = MODE_MENU;

  // Load fonts and audio
  // Initialize game state, graphics, sound, and controllers here
  state = new GameLogic();

  //loads necessary resources to the resource manager
  resources.LoadFont("old_school", "../data/Old-School-Adventures.ttf");
  resources.LoadXML("text", "../data/game-text.xml");

  curr_player_view = std::make_shared<MenuView>(state, app);

  views.push_back(curr_player_view);

  //starts clock
  time.restart();
};

Engine::~Engine()
{
  delete state;
}

/**
 * Update the game state.
 */
void Engine::update_state(float delta)
{
  if (curr_game_mode == MODE_PLAY)
  {
    if (!state->is_paused()) state->update_state();
  }
  if (state->shutdown()) App->close();
}

/**
 * Update the sound and graphics.
 */
void Engine::update_views(float delta)
{
	// centers view on player while game is in play
  for (const auto &view : views)
  {
    view->update(delta);
  }
}

void Engine::update_graphics()
{
  curr_player_view->draw();
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
void Engine::switch_mode()
{
	//vectors are emptied upon change of mode
	views.clear();

	//places the primary controller and view for the mode at the 0th index of each vector
	switch (curr_game_mode)
	{
	case MODE_MENU:
//		controllers.push_back(std::make_shared<MenuView>(state));
//		views.push_back(std::make_shared<MenuGraphics>(state));
		break;
	case MODE_PLAY:
//		controllers.push_back(std::make_shared<GameView>(state));
//		views.push_back(std::make_shared<PlayerGraphics>(state));
		break;
	case MODE_LEVEL_SELECT:
		break;
	case MODE_SHOP:
		break;
	}
}

