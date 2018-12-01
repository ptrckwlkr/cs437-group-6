#ifndef CSCI437_VIEW_H
#define CSCI437_VIEW_H

#include "game_logic.h"
#include "Animations/Animation.h"

/**
 * Abstract base class for all controllers.
 */
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
    //Animation getPlayerAnimation(){ return  animation_player;}
    //Animation getSkeletonAnimation(){ return  animation_skeleton;}

protected:
    GameLogic *state;
    long long id;
    //to be used to update sprite movement
//    Animation animation_player;
//    Animation animation_skeleton;
//    sf::Texture skeleton_text;
//    sf::Texture player_text;

};

#endif //CSCI437_VIEW_H
