#include <events/event_victory.h>
#include "Animations/ExplosionAnimation.h"
#include "EntityManager.h"

ExplosionAnimation::ExplosionAnimation(Explosion &entity) : Animation(), explosion(&entity)
{
  texture = resources.GetTexture("explosionTexture");
  imageCount = sf::Vector2u(5, 5);
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
  sprite.setPosition(explosion->get_position().x, explosion->get_position().y - 50);
}

void ExplosionAnimation::update(float delta)
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
  if (slide == 24) {
    EntityManager::Instance().removeEntity(explosion->id);
    EventVictory e;
    EventManager::Instance().sendEvent(e);
  }
  sprite.setTextureRect(uvRect);
  sprite.setScale(3, 3);
}

