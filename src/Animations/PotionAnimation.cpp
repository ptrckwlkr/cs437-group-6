#include "Animations/PotionAnimation.h"

PotionAnimation::PotionAnimation(Potion &entity) : Animation(), potion(&entity)
{
    texture = resources.GetTexture("potionTexture");
    imageCount = sf::Vector2u(2, 3);
    currentImage.x = 0;
    currentImage.y = potion->type_num;
    uvRect.width = texture.getSize().x / imageCount.x;
    uvRect.height = texture.getSize().y / imageCount.y;
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
    sprite.setTexture(texture);
    sprite.setTextureRect(uvRect);
    sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2));
    sprite.setPosition(potion->get_position().x, potion->get_position().y);
    sprite.setScale(2.5f, 2.5f);
}

void PotionAnimation::update(float delta)
{
    //since it is a static image update has no function
}
