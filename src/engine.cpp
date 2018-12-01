#include <SFML/Window/Event.hpp>
#include "engine.h"
#include "views/player_view_menu.h"
#include "views/player_view_game.h"
#include "views/player_view_level_select.h"
#include "views/view_manager.h"
#include "EntityManager.h"

Engine &Engine::getInstance()
{
  static Engine instance;
  return instance;
}

void Engine::init(sf::RenderWindow *app)
{
  //loads necessary resources to the resource manager
  resources.LoadFont("old_school", "../data/Fonts/Old-School-Adventures.ttf");
  resources.LoadXML("text", "../data/xml/game-text.xml");
  resources.LoadTexture("map", "../data/Images/map.png");
  resources.LoadTexture("fog", "../data/Images/vignette.png");
  resources.LoadTexture("tileset", "../data/Tiles/tilesheet.png");
  resources.LoadTexture("playerTexture", "../data/Sprites/playerSprite.png");
  resources.LoadTexture("skeletonTexture", "../data/Sprites/skeletonSprite.png");
  if (MUSIC) resources.LoadMusic("vanquisher", "../data/Music/BRPG_Vanquisher_FULL_Loop.wav");
  resources.LoadXML("enemies", "../data/xml/enemies.xml");

  App = app;
  curr_game_mode = MODE_MENU;
  state = GameLogic();
  ViewManager::Instance()->init(&state);
  ViewManager::Instance()->set_player_view<MenuView>(&state, App);

  //starts clock
  time.restart();
}

/**
 * Update all the game views.
 */
void Engine::update_views(float delta)
{
  ViewManager::Instance()->update_views(delta);
}

/**
 * Update the game state.
 */
void Engine::update_state(float delta)
{
  switch_mode();
  if (curr_game_mode == MODE_PLAY)
  {
    if (!state.is_paused()) state.update_state();
  }
}

void Engine::update_graphics(float delta)
{
  ViewManager::Instance()->get_player_view()->draw(delta);
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
void Engine::set_mode(GameMode mode)
{
  curr_game_mode = mode;
}

void Engine::switch_mode()
{
  static GameMode old_mode = curr_game_mode;

  if (curr_game_mode != old_mode)
  {
    old_mode = curr_game_mode;
    ViewManager::Instance()->reset();

    //places the primary controller and view for the mode at the 0th index of each vector
    switch (curr_game_mode)
    {
      case MODE_MENU:
        ViewManager::Instance()->set_player_view<MenuView>(&state, App);
        break;
      case MODE_LEVEL_SELECT:
        ViewManager::Instance()->set_player_view<LevelSelectView>(&state, App);
	      break;
      case MODE_SHOP:
        break;
      case MODE_PLAY:
        state.create_new_level(AGENT_BASED);
        ViewManager::Instance()->set_player_view<GameView>(&state, App);
        break;
        case MODE_VICTORY:
            //ViewManager::Instance()->set_player_view(<VictoryView>(&state, App);
          break;

    }
  }
}

void Engine::shutdown()
{
  ViewManager::Instance()->reset();
  EntityManager::Instance()->reset();
  EventManager::Instance()->reset();
  App->close();
}
