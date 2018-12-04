#include "Animations/OrcAnimation.h"

OrcAnimation::OrcAnimation(Orc &entity) : Animation(), orc(&entity) {
    texture = resources.GetTexture("orcTexture");
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
    sprite.setPosition(orc->get_position().x, orc->get_position().y);
    prev_pos = orc->get_position();

    if (orc->type == "orc-green")
    {
        sprite.setColor(sf::Color(0,255,96));
    }
    else if (orc->type == "orc-red")
    {
        sprite.setColor(sf::Color(255,50,128));
        switchTime =  7.1f/60.f;
    }
    else if (orc->type == "orc-gold")
    {
        sprite.setColor(sf::Color(255,200,0));
        switchTime = 6.2f/60.f;
    }
}


void OrcAnimation::update(float delta){
    //imageCount is the specific value for the number of animation
    //for a certain movement base on the sprite sheet
    unsigned int imageCount = 9;
    Vector2D dir = orc->get_position() - orc->get_old_position();

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

    if ( totalTime >= switchTime && !(prev_pos == orc->get_position())){
        totalTime = 0.0f;
        currentImage.x++;
        if (currentImage.x >= this->imageCount.x){
            currentImage.x =0;
        }
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.top = currentImage.y * uvRect.height;
    }

    sprite.setTextureRect(uvRect);
    sprite.setPosition(orc->get_position().x, orc->get_position().y);
    prev_pos = orc->get_position();
}
