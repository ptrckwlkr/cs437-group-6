#include "mode_play.h"
#include "mode_menu.h"
#include "game_logic.h"

GameLogic::GameLogic()
{
  set_mode(MODE_MENU);
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
	  curr_mode = std::make_shared<MenuMode>();
      break;
    case MODE_SHOP:
      break;
    case MODE_MAP:
      break;
    case MODE_PLAY:
      curr_mode = std::make_shared<PlayMode>();
      break;
  }
  curr_game_mode = mode;
  changed_mode = true;
}

/*
	Returns true if the mode has changed and false otherwise. Allows the vectors of
	Controllers and Views to be updated in engine.cpp based on input read from the controller
*/
bool GameLogic::has_mode_changed()
{
	return changed_mode;
}