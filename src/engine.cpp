#include <SFML/Window/Event.hpp>
#include <views/player_view_story.h>
#include <views/player_next_level.h>
#include "views/player_view_victory.h"
#include "views/player_view_level_select.h"
#include "views/player_view_inventory.h"
#include "engine.h"
#include "views/player_view_menu.h"
#include "views/player_view_game.h"
#include "views/player_view_level_select.h"
#include "views/player_view_shop.h"
#include "views/player_view_lost.h"
#include "view_manager.h"
#include "EntityManager.h"

Engine &Engine::Instance()
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
  ViewManager::Instance().init(&state);
  ViewManager::Instance().set_player_view<MenuView>(&state, App);
  
  //starts clock
  time.restart();
}

/**
 * Update all the game views.
 */
void Engine::update_views(float delta)
{
  ViewManager::Instance().update_player_view(delta);
  if (curr_game_mode == MODE_PLAY && !state.is_paused()) ViewManager::Instance().update_views(delta);
}

/**
 * Update the game state.
 */
void Engine::update_state(float delta)
{
  if (curr_game_mode == MODE_PLAY)
  {
    if (!state.is_paused()) state.update_state(delta);
  }
}

void Engine::update_graphics(float delta)
{
  ViewManager::Instance().get_player_view()->draw(delta);
}

/**
 * Update elapsed time to regulate main game loop.
 */
float Engine::clock()
{
	return time.restart().asSeconds() * GAME_CLOCK_SCALER;
}

void Engine::shutdown()
{
  ViewManager::Instance().reset();
  EntityManager::Instance().reset();
  EventManager::Instance().reset();
  App->close();
}

void Engine::start_new_game(int level)
{
  state.reset();
  state.get_player_data().reset();
  if (level < 8) state.create_new_level(AGENT_BASED, level);
  else state.create_new_level(LEVEL_FILE, level);
}

void Engine::switch_mode(GameMode mode)
{
  sf::FloatRect viewport = App->getView().getViewport();

  curr_game_mode = mode;
  switch (mode)
  {
      case MODE_MENU:
        ViewManager::Instance().set_player_view<MenuView>(&state, App);
            break;
      case MODE_LEVEL_SELECT:
        ViewManager::Instance().set_player_view<LevelSelectView>(&state, App);
            break;
      case MODE_SHOP:
        ViewManager::Instance().set_player_view<ShopView>(&state, App);
            break;
      case MODE_PLAY:
        ViewManager::Instance().set_player_view<GameView>(&state, App);
            break;
      case MODE_VICTORY:
        ViewManager::Instance().set_player_view<VictoryView>(&state, App);
            break;
      case MODE_LOST:
        ViewManager::Instance().set_player_view<LostView>(&state, App);
            break;
      case MODE_STORY:
        ViewManager::Instance().set_player_view<StoryView>(&state, App);
            break;
      case MODE_INVENTORY:
        ViewManager::Instance().set_player_view<InventoryView>(&state, App);
            break;
      case MODE_NEXT_LEVEL:
        ViewManager::Instance().set_player_view<NextLevelView>(&state, App);
            break;
    }

    //prevents viewport changes from being discarded when mode is switched
    sf::View sf_view = App->getView();
    sf_view.setViewport(viewport);
    App->setView(sf_view);


}

