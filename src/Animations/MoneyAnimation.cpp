#include "Animations/MoneyAnimation.h"
#include "EntityManager.h"

MoneyAnimation::MoneyAnimation(Money &entity) : Animation(), money(&entity)
{
  texture = resources.GetTexture("moneyTexture");
  imageCount = sf::Vector2u(4, 4);
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
  sprite.setPosition(money->get_position().x, money->get_position().y - 25);
}

void MoneyAnimation::update(float delta)
{
  totalTime += delta;
  if (totalTime > switchTime){
    slide++;
    totalTime = 0.0f;
    currentImage.x = slide % 4;
    currentImage.y = slide / 4;
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
  }
  if (slide == 15) EntityManager::Instance().removeEntity(money->id);
  sprite.setTextureRect(uvRect);
}
