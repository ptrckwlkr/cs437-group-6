#ifndef CSCI437_LOGIC_H
#define CSCI437_LOGIC_H

/**
 * Organize and coordinate the game state.
 */
class GameLogic
{
public:
    GameLogic();

    void update_state();
    void toggle_pause() {f_paused = !f_paused;}
    bool is_paused() {return f_paused;}
    bool shutdown() {return f_shutdown;}
    void exit();

private:

    bool f_paused;
    bool f_shutdown;
};

#endif //CSCI437_LOGIC_H
