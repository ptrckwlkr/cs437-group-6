#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);

    uvRect.left = currentImage.x;
    uvRect.top = texture->getSize().y / float(imageCount.y);

}

Animation::~Animation(){}

void Animation::Update(int row, int imageCount, float delta){
    currentImage.y = row; //same as the enum of picking which animation to do
    this->imageCount.x = imageCount;
    totalTime += delta;

    if ( totalTime >= switchTime){
        totalTime -= switchTime;
        currentImage.x++;
        if (currentImage.x >= this->imageCount.x){
            currentImage.x =0;
        }
    }
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;

}