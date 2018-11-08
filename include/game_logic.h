#ifndef CSCI437_LOGIC_H
#define CSCI437_LOGIC_H

#include "level.h"
#include "level_factory.h"
#include "mode.h"
#include "player_data.h"
#include "EventManager.h"

enum GameMode
{
    MODE_MENU,
    MODE_SHOP,
    MODE_MAP,
    MODE_PLAY,
};

/**
 * Organize and coordinate the game state.
 */
class GameLogic
{
public:
    GameLogic();
    ~GameLogic() = default;

    void update_state();
    void toggle_pause() {f_paused = !f_paused;}
    bool is_paused() {return f_paused;}
    bool shutdown() {return f_shutdown;}
		bool has_mode_changed();
    void exit();
    void set_mode(GameMode mode);

    std::shared_ptr<Mode> &get_mode() {return curr_mode;}
		std::shared_ptr<PlayerData> &get_player_data() {return player_data;}

		GameMode get_gameMode() { return curr_game_mode; } //allows engine to see GameMode
		/*engine is done making necessary initial updates for mode change so it updates changed_mode
			to prevent performing these initial updates a second time*/
		void finished_mode_change() { changed_mode = false; }

private:
    std::shared_ptr<Mode> curr_mode;
		std::shared_ptr<PlayerData> player_data;
    bool f_paused;
    bool f_shutdown;

		GameMode curr_game_mode;
		bool changed_mode;
};

#endif //CSCI437_LOGIC_H
