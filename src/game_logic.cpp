#include <view_manager.h>
#include "game_logic.h"

GameLogic::GameLogic()
{
  level_factory = LevelFactory();
  player_data = PlayerData();
  collision_engine = CollisionEngine();
  f_paused = false;
}

/**
 * Update the game state
 */
void GameLogic::update_state()
{
  collision_engine.hash_entities(level->get_map(), EntityManager::Instance()->getEntites());
  level->update();
  collision_engine.check_collisions(level->get_map(), EntityManager::Instance()->getEntites());
  EventManager::Instance()->process();//ProcessEvents();
}

/**
 * Start a new level.
 */
void GameLogic::create_new_level(Generator g)
{
  // TODO Should probably load level parameters from an XML file and set the Level Factory accordingly
  level_factory.set_algorithm(g);
  level = level_factory.generate_level();
}

void GameLogic::reset()
{
  EventManager::Instance()->ClearEvents();
  for (const auto &e : EntityManager::Instance()->getEntites())
  {
    EventManager::Instance()->UnregisterAll(e.get());
  }
  collision_engine.reset();
  EntityManager::Instance()->ClearAll();
  ViewManager::Instance()->clear();
}
