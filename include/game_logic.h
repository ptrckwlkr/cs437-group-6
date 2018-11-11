#ifndef CSCI437_LOGIC_H
#define CSCI437_LOGIC_H

#include "level.h"
#include "level_factory.h"
#include "mode.h"

enum GameMode
{
    MODE_MENU,
    MODE_SHOP,
    MODE_MAP,
    MODE_PLAY,
    MODE_LEVEL_SELECT,
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
    void exit();
    void set_mode(GameMode mode);
    std::shared_ptr<Mode> &get_mode() {return curr_mode;}

private:
    std::shared_ptr<Mode> curr_mode;
    bool f_paused;
    bool f_shutdown;
};

#endif //CSCI437_LOGIC_H
