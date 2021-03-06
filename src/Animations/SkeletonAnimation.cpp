#include "Animations/SkeletonAnimation.h"

SkeletonAnimation::SkeletonAnimation(Skeleton &entity) : Animation(), skeleton(&entity) {
    texture = resources.GetTexture("skeletonTexture");
    imageCount = sf::Vector2u(13, 21);
    switchTime = 8/60.f;
    totalTime = 0.0f;
    currentImage.x = 0;
    currentImage.y = 10;
    uvRect.width = texture.getSize().x / imageCount.x;
    uvRect.height = texture.getSize().y / imageCount.y;
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
    sprite.setTexture(texture);
    sprite.setTextureRect(uvRect);
    sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f + 15.f ));
    sprite.setPosition(skeleton->get_position().x, skeleton->get_position().y);
    prev_pos = skeleton->get_position();

    if (skeleton->type == "skeleton-red")
    {
        sprite.setColor(sf::Color(255,128,128));
        switchTime =  7.1f/60.f;
    }
    else if (skeleton->type == "skeleton-gold")
    {
        sprite.setColor(sf::Color(255,215,0));
        switchTime = 6.2f/60.f;
    }
}


SkeletonAnimation::~SkeletonAnimation(){}

void SkeletonAnimation::update(float delta){
    //imageCount is the specific value for the number of animation
    //for a certain movement base on the sprite sheet
    unsigned int imageCount = 9;
    Vector2D dir = skeleton->get_position() - skeleton->get_old_position();

    if (dir.y < 0 && fabs(dir.y) > fabs(dir.x))
        currentImage.y = 8;
    else if (dir.y > 0 && fabs(dir.y) > fabs(dir.x))
        currentImage.y = 10;
    else if (dir.x < 0 && fabs(dir.x) > fabs(dir.y))
        currentImage.y = 9;
    else if (dir.x > 0 && fabs(dir.x) > fabs(dir.y))
        currentImage.y = 11;

    this->imageCount.x = imageCount;
    totalTime += delta;

    if ( totalTime >= switchTime && !(prev_pos == skeleton->get_position())){
        totalTime = 0.0f;
        currentImage.x++;
        if (currentImage.x >= this->imageCount.x){
            currentImage.x =0;
        }
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.top = currentImage.y * uvRect.height;
    }

    sprite.setTextureRect(uvRect);
    sprite.setPosition(skeleton->get_position().x, skeleton->get_position().y);
    prev_pos = skeleton->get_position();
}
