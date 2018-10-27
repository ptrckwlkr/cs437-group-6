#include "game_logic.h"

GameLogic::GameLogic()
{

  // TODO Create a level through some system
  level_factory = new LevelFactory();
  level_factory->set_algorithm(LEVEL_FILE);
  curr_level = level_factory->generate_level();
  // curr_level->get_map()->print_map();

  f_paused = false;
  f_shutdown = false;
}

GameLogic::~GameLogic()
{
  delete level_factory;
}

/**
 * Update the game state
 */
void GameLogic::update_state()
{
  curr_level->update();
}

/**
 * Sends a signal that the application should shutdown.
 */
void GameLogic::exit()
{
  f_shutdown = true;
}
