#ifndef CSCI437_ANIMATION_H
#define CSCI437_ANIMATION_H

#include <SFML/Graphics.hpp>
#include "vector2d.h"


enum Direction{
    WALK_UP = 8,
    WALK_LEFT = 9,
    WALK_DOWN = 10,
    WALK_RIGHT = 11,

};

class Animation 
{
    private:
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;

        float totalTime;
        float switchTime;
    public:
        sf::IntRect uvRect;
        sf::Sprite sprite;

    public:
        Animation();
        void init(sf::Texture &texture, sf::Vector2u imageCount, float switchTime);
        ~Animation();
        void Update(Vector2D dir, int imageCount, float delta);
        sf::Sprite &getSprite(){ return sprite;}
};

#endif //CSCI437_ANIMATION_H