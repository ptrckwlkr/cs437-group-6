#ifndef CSCI437_PLAYERANIMATION_H
#define CSCI437_PLAYERANIMATION_H

#include <entities/Player.h>
#include "Animation.h"


class PlayerAnimation: public Animation {

public:
    PlayerAnimation(Player &entity, sf::Texture &texture, sf::Vector2u imageCount, float switchTime);
    ~PlayerAnimation();
    //void initSprite(sf::Texture &texture, sf::Vector2u imageCount, float switchTime);
    virtual void update(float delta) = 0;

private:
    Player *player;
//    float totalTime;
//    float switchTime;
//    sf::IntRect uvRect;

//    sf::Texture texture;
//    sf::Vector2u imageCount;
//    sf::Vector2u currentImage;



};


#endif //CSCI437_PLAYERANIMATION_H
