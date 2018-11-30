#ifndef CSCI437_VIEW_H
#define CSCI437_VIEW_H

/**
 * Abstract base class for all controllers.
 */
class GameLogic;
class View
{

public:
    explicit View(GameLogic *state) : state(state)
    {
      static long long view_id = 0;
      id = view_id++;
    };
    ~View() = default;
    virtual void update(float delta) = 0;
    GameLogic &get_state() {return *state;}
    long long get_id() {return id;}

protected:
    GameLogic *state;
    long long id;

};

#endif //CSCI437_VIEW_H
