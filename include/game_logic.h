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
    void create_new_level(Generator g);
    void toggle_pause() {f_paused = !f_paused;}
    bool is_paused() {return f_paused;}
		void reset();
		Level &get_level() {return *level;}
		PlayerData &get_player_data() {return player_data;}

private:
		LevelFactory level_factory;
    PlayerData player_data;
		CollisionEngine collision_engine;
		std::shared_ptr<Level> level;
    bool f_paused;
};

#endif //CSCI437_LOGIC_H
