#ifndef CSCI437_LOGIC_H
#define CSCI437_LOGIC_H

#include "level.h"
#include "level_factory.h"

/**
 * Organize and coordinate the game state.
 */
class GameLogic
{
public:
    GameLogic();
    ~GameLogic();

    void update_state();
    void toggle_pause() {f_paused = !f_paused;}
    bool is_paused() {return f_paused;}
    bool shutdown() {return f_shutdown;}
    void exit();

    LevelFactory *level_factory;
    std::shared_ptr<Level> get_level() {return curr_level;}

private:
    std::shared_ptr<Level> curr_level;
    // std::shared_ptr<Mode> curr_mode; TODO

    bool f_paused;
    bool f_shutdown;
};

#endif //CSCI437_LOGIC_H
