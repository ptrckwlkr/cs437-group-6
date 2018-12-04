#include "Animations/SmokeAnimation.h"
#include "EntityManager.h"

SmokeAnimation::SmokeAnimation(Smoke &entity) : Animation(), smoke(&entity)
{
  texture = resources.GetTexture("smokeTexture");
  imageCount = sf::Vector2u(3, 2);
  switchTime = 0.2f;
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
  sprite.setPosition(smoke->get_position().x, smoke->get_position().y -45);
}

void SmokeAnimation::update(float delta)
{
  totalTime += delta;
  if (totalTime > switchTime){
    slide++;
    totalTime = 0.0f;
    currentImage.x = slide % 3;
    currentImage.y = slide / 3;
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
  }
  if (slide == 5) EntityManager::Instance().removeEntity(smoke->id);
  sprite.setTextureRect(uvRect);
}
