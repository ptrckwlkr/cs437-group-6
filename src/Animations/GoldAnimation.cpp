#include "Animations/GoldAnimation.h"

GoldAnimation::GoldAnimation(Gold &entity) : Animation(), gold(&entity)
{
  texture = resources.GetTexture("goldTexture");
  imageCount = sf::Vector2u(5, 4);
  switchTime = 0.2f;
  totalTime = 0.0f;
  currentImage.x = 0;
  currentImage.y = (unsigned int)(rand() % 4);
  uvRect.width = texture.getSize().x / imageCount.x;
  uvRect.height = texture.getSize().y / imageCount.y;
  uvRect.left = currentImage.x * uvRect.width;
  uvRect.top = currentImage.y * uvRect.height;
  sprite.setTexture(texture);
  sprite.setTextureRect(uvRect);
  sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2));
  sprite.setPosition(gold->get_position().x, gold->get_position().y);
  random_interval = 3 + (float)rand() / (float)(RAND_MAX / 7);
}

void GoldAnimation::update(float delta)
{
  totalTime += delta;
  if (totalTime > random_interval){
    if (totalTime > random_interval + switchTime)
    {
      slide++;
      totalTime = random_interval;
    }
    if (slide == 5)
    {
      slide = 0;
      totalTime = 0.0f;
      currentImage.x = slide;
      random_interval = 3 + (float)rand() / (float)(RAND_MAX / 7);
    }
    currentImage.x = slide;
    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
  }
  sprite.setTextureRect(uvRect);
}
