#include "game_logic.h"
#include "views/view_manager.h"
#include "EntityManager.h"

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
  EventManager::Instance()->processEvents(); // Process all other events
  collision_engine.hash_entities(level->get_map(), EntityManager::Instance()->getEntites());
  level->update();
  collision_engine.check_collisions(level->get_map());
  EventManager::Instance()->processEvents(); // Process collisions
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
  collision_engine.reset();
  ViewManager::Instance()->reset();
  EntityManager::Instance()->reset();
  EventManager::Instance()->reset();
}
