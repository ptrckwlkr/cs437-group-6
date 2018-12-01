#include "Animations/Animation.h"

Animation::Animation(){
}

void Animation::initSprite(sf::Texture &texture, sf::Vector2u imageCount, float switchTime)
{
    sprite.setTexture(texture);
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture.getSize().x / float(imageCount.x);
    uvRect.height = texture.getSize().y / float(imageCount.y);

    uvRect.left = currentImage.x;
    uvRect.top = texture.getSize().y / float(imageCount.y);
    sprite.setTextureRect(uvRect);

}

Animation::~Animation(){}

//void Animation::Update(Vector2D dir, int imageCount, float delta){
//
//    ///get current sprite when the direction is passed
//    //playergame view can access this current sprite to draw it
//    if ( dir.y == -1)
//        currentImage.y = 8;
//    else if (dir.y == 1 )
//        currentImage.y = 10;
//    else if (dir.x == -1 )
//        currentImage.y = 9;
//    else if ( dir.x == 1)
//        currentImage.y = 11;
//
//    this->imageCount.x = imageCount;
//    totalTime += delta;
//
//    if ( totalTime >= switchTime){
//        totalTime = 0.0f;
//        currentImage.x++;
//        if (currentImage.x >= this->imageCount.x){
//            currentImage.x =0;
//        }
//        uvRect.left = currentImage.x * uvRect.width;
//        uvRect.top = currentImage.y * uvRect.height;
//
//        sprite.setTextureRect(uvRect);
//    }
//}