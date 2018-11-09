#include "game_logic.h"

GameLogic::GameLogic()
{
  level_factory = LevelFactory();
  player_data = PlayerData();
  f_paused = false;
}

/**
 * Update the game state
 */
void GameLogic::update_state()
{
  level->update();
  EventManager::Instance()->ProcessEvents();
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
