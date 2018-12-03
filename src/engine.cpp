#include <SFML/Window/Event.hpp>
#include <views/player_view_story.h>
#include "views/player_view_victory.h"
#include "views/player_view_level_select.h"
#include "views/player_view_inventory.h"
#include "engine.h"
#include "views/player_view_menu.h"
#include "views/player_view_game.h"
#include "views/player_view_level_select.h"
#include "views/player_view_shop.h"
#include "views/player_view_lost.h"
#include "views/view_manager.h"
#include "EntityManager.h"

Engine &Engine::getInstance()
{
  static Engine instance;
  return instance;
}

void Engine::init(sf::RenderWindow *app)
{
  App = app;
  //loads necessary resources to the resource manager
  resources.LoadAllResources();
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
        ViewManager::Instance()->set_player_view<ShopView>(&state, App);
        break;
      case MODE_PLAY:
        ViewManager::Instance()->set_player_view<GameView>(&state, App);
        break;
      case MODE_VICTORY:
        ViewManager::Instance()->set_player_view<VictoryView>(&state, App);
        break;
      case MODE_LOST:
        ViewManager::Instance()->set_player_view<LostView>(&state, App);
      case MODE_STORY:
        ViewManager::Instance()->set_player_view<StoryView>(&state, App);
            break;
      case MODE_INVENTORY:
        ViewManager::Instance()->set_player_view<InventoryView>(&state, App);
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

void Engine::start_new_game(int level)
{
  state.create_new_level(AGENT_BASED);
}
