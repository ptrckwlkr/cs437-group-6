#ifndef CSCI437_LOGIC_H
#define CSCI437_LOGIC_H

#include "level.h"
#include "level_factory.h"
#include "player_data.h"
#include "EventManager.h"

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
    void exit();
		std::shared_ptr<Level> get_level() {return level;}
		std::shared_ptr<PlayerData> &get_player_data() {return player_data;}

private:
		LevelFactory *level_factory;
		std::shared_ptr<Level> level;
		std::shared_ptr<PlayerData> player_data;
    bool f_paused;
    bool f_shutdown;
};

#endif //CSCI437_LOGIC_H
