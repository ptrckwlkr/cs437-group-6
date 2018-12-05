#ifndef CSCI437_LOGIC_H
#define CSCI437_LOGIC_H

#include <memory>
#include "level.h"
#include "level_factory.h"
#include "player_data.h"
#include "collision_engine.h"
#include "events/event_exit_reached.h"
#include "events/event_player_died.h"
#include "events/event_victory.h"

/**
 * Organize and coordinate the game state.
 */
class GameLogic : public Listener {
public:
    GameLogic();

    ~GameLogic();

    void update_state(float delta);

    void create_new_level(Generator g, int level_num);

    void toggle_pause() { f_paused = !f_paused; }

    bool is_paused() { return f_paused; }

    void reset();
    void reset_level_factory() {level_factory.reset();}

    Level &get_level() { return *level; }

    PlayerData &get_player_data() { return player_data; }

    int get_level_num() { return current_level; }

private:
    LevelFactory level_factory;
    PlayerData player_data;
    CollisionEngine collision_engine;
    std::shared_ptr<Level> level;

    int current_level;

    bool f_paused = false;
    bool f_floor_complete = false;
    bool f_victory = false;
    bool f_defeat = false;
    bool check_flags();
		void handleExitReached(const EventExitReached &event);
		void handlePlayerDeath(const EventPlayerDied &event);
		void handleVictory(const EventVictory &event);

};

#endif //CSCI437_LOGIC_H
