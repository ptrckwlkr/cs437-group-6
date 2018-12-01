
#include "Animations/PlayerAnimation.h"

PlayerAnimation::PlayerAnimation(Player &entity, sf::Texture &texture, sf::Vector2u imageCount, float switchTime ){
    this->player = &entity;
    Animation::initSprite(texture, imageCount, switchTime);

}
PlayerAnimation::~PlayerAnimation(){}

//void PlayerAnimation::initSprite(sf::Texture &texture, sf::Vector2u imageCount, float switchTime){
//    Animation::initSprite(texture, imageCount, switchTime);
//
//}

void PlayerAnimation::update(float delta){
    //imageCount is the specific value for the number of animation
    //for a certain movement base on the sprite sheet
    int imageCount = 9;
    Vector2D oldpos = player.get_old_position();
    //Vector2D currpos = player.get_position();
//    if ( dir.y == -1)
    if (oldpos.y = -1)
        currentImage.y = 8;
    else if (oldpos.y == 1 )
        currentImage.y = 10;
    else if (oldpos.x == -1 )
        currentImage.y = 9;
    else if (oldpos.x == 1)
        currentImage.y = 11;

    this->imageCount.x = imageCount;
    totalTime += delta;

    if ( totalTime >= switchTime){
        totalTime = 0.0f;
        currentImage.x++;
        if (currentImage.x >= this->imageCount.x){
            currentImage.x =0;
        }
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.top = currentImage.y * uvRect.height;

        sprite.setTextureRect(uvRect);
    }
}