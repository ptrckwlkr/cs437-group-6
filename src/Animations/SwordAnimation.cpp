#include "Animations/SwordAnimation.h"
#include "EntityManager.h"

SwordAnimation::SwordAnimation(Sword &entity) : Animation(), sword(&entity)
{
  Vector2D player_pos = EntityManager::Instance().getPlayer()->get_position();
  offset_x = entity.get_position().x - player_pos.x;
  offset_y = entity.get_position().y - player_pos.y;

  texture = resources.GetTexture("swordTexture");
  imageCount = sf::Vector2u(2, 2);
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
  sprite.setPosition(player_pos.x + offset_x, player_pos.y + offset_y - 10);
}

void SwordAnimation::update(float delta)
{
  Vector2D player_pos = EntityManager::Instance().getPlayer()->get_position();
  totalTime += delta;
  if (totalTime > switchTime){
    slide++;
    totalTime = 0.0f;
    currentImage.x = slide % 2;
    currentImage.y = slide / 2;
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
  }
  if (slide == 3) EntityManager::Instance().removeEntity(sword->id);
  sprite.setTextureRect(uvRect);
  sprite.setScale(2.0, 2.0);
  sprite.setRotation(sword->getAngle());
  sprite.setPosition(player_pos.x + offset_x, player_pos.y + offset_y - 10);
}
