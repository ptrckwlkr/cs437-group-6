#include "Animations/BloodAnimation.h"
#include "EntityManager.h"

BloodAnimation::BloodAnimation(Blood &entity) : Animation(), blood(&entity)
{
  texture = resources.GetTexture("bloodTexture");
  imageCount = sf::Vector2u(5, 3);
  switchTime = 0.1f;
  totalTime = 0.0f;
  currentImage.x = 0;
  currentImage.y = 0;
  uvRect.width = texture.getSize().x / imageCount.x;
  uvRect.height = texture.getSize().y / imageCount.y;
  uvRect.left = currentImage.x * uvRect.width;
  uvRect.top = currentImage.y * uvRect.height;
  sprite.setTexture(texture);
  sprite.setTextureRect(uvRect);
  sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2));
  sprite.setPosition(blood->get_position().x, blood->get_position().y);
}

void BloodAnimation::update(float delta)
{
  totalTime += delta;
  if (totalTime > switchTime){
    slide++;
    totalTime = 0.0f;
    currentImage.x = slide % 5;
    currentImage.y = slide / 5;
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
  }
  if (slide == 14) EntityManager::Instance().removeEntity(blood->id);
  sprite.setTextureRect(uvRect);
}
