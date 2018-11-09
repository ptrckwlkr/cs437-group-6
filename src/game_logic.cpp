#include "game_logic.h"

GameLogic::GameLogic()
{
  level_factory = new LevelFactory();
  level_factory->set_algorithm(LEVEL_FILE);
  level = level_factory->generate_level();

  player_data = std::make_shared<PlayerData>();
  f_paused = false;
  f_shutdown = false;
}

/**
 * Update the game state
 */
void GameLogic::update_state()
{
  level->update();
}

/**
 * Sends a signal that the application should shutdown.
 */
void GameLogic::exit()
{
  f_shutdown = true;
}
