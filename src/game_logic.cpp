#include "mode_play.h"
#include "game_logic.h"

GameLogic::GameLogic()
{
  set_mode(MODE_PLAY);
  f_paused = false;
  f_shutdown = false;
}

/**
 * Update the game state
 */
void GameLogic::update_state()
{
  curr_mode->update();
}

/**
 * Sends a signal that the application should shutdown.
 */
void GameLogic::exit()
{
  f_shutdown = true;
}

void GameLogic::set_mode(GameMode mode)
{
  switch (mode)
  {
    case MODE_MENU:
      break;
    case MODE_SHOP:
      break;
    case MODE_MAP:
      break;
    case MODE_PLAY:
      curr_mode = std::make_shared<PlayMode>();
      break;
  }
}
