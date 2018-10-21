#include "game_logic.h"

GameLogic::GameLogic()
{
  f_paused = false;
  f_shutdown = false;
}

/**
 * Update the game state
 */
void GameLogic::update_state()
{

}

/**
 * Sends a signal that the application should shutdown.
 */
void GameLogic::exit()
{
  f_shutdown = true;
}
