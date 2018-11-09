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
}

void GameLogic::create_new_level(Generator g)
{
  level_factory.set_algorithm(g);
  level = level_factory.generate_level();
}
