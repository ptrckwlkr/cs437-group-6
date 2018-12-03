#include "Animations/GhostAnimation.h"


GhostAnimation::GhostAnimation(Ghost &entity) : Animation(), ghost(&entity) {
    texture = resources.GetTexture("ghostTexture");
    imageCount = sf::Vector2u(3, 4);
    switchTime = 8/60.f;
    totalTime = 0.0f;
    currentImage.x = 0;
    currentImage.y = 0;
    uvRect.width = texture.getSize().x / imageCount.x;
    uvRect.height = texture.getSize().y / imageCount.y;
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
    sprite.setTexture(texture);
    sprite.setTextureRect(uvRect);
    sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f + 15.f));
    sprite.setPosition(ghost->get_position().x, ghost->get_position().y);

    if (ghost->type == "ghost-red")
    {
        sprite.setColor(sf::Color(255,128,128));
        switchTime =  7/60.f;
    }
    else if (ghost->type == "ghost-gold")
    {
        sprite.setColor(sf::Color(255,215,0));
        switchTime = 6/60.f;
    }
}


void GhostAnimation::update(float delta){
    //imageCount is the specific value for the number of animation
    //for a certain movement base on the sprite sheet
    unsigned int imageCount = 3;
    Vector2D dir = ghost->get_position() - ghost->get_old_position();

    if (dir.y < 0 && fabs(dir.y) > fabs(dir.x))
        currentImage.y = 3;
    else if (dir.y > 0 && fabs(dir.y) > fabs(dir.x))
        currentImage.y = 0;
    else if (dir.x < 0 && fabs(dir.x) > fabs(dir.y))
        currentImage.y = 1;
    else if (dir.x > 0 && fabs(dir.x) > fabs(dir.y))
        currentImage.y = 2;

    this->imageCount.x = imageCount;
    totalTime += delta;

    if ( totalTime >= switchTime){
        totalTime = 0.0f;
        currentImage.x++;
        if (currentImage.x >= this->imageCount.x){
            currentImage.x = 0;
        }
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.top = currentImage.y * uvRect.height;
    }

    sprite.setTextureRect(uvRect);
    sprite.setPosition(ghost->get_position().x, ghost->get_position().y);
}