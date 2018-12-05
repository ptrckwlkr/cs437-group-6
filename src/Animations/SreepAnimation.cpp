#include "Animations/SreepAnimation.h"

SreepAnimation::SreepAnimation(Sreep &entity) : Animation(), sreep(&entity) {
  texture = resources.GetTexture("sreepTexture");
  imageCount = sf::Vector2u(8, 5);
  switchTime = 8/60.f;
  totalTime = 0.0f;
  currentImage.x = 2;
  currentImage.y = 4;
  uvRect.width = texture.getSize().x / imageCount.x;
  uvRect.height = texture.getSize().y / imageCount.y;
  uvRect.left = currentImage.x * uvRect.width;
  uvRect.top = currentImage.y * uvRect.height;
  sprite.setTexture(texture);
  sprite.setTextureRect(uvRect);
  sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f));
  sprite.setPosition(sreep->get_position().x, sreep->get_position().y);
  prev_pos = sreep->get_position();
  facing = FRONT;
}


SreepAnimation::~SreepAnimation(){}

void SreepAnimation::update(float delta){

  Vector2D dir = sreep->get_position() - sreep->get_old_position();
  totalTime += delta;

  if (totalTime >= switchTime){
    prev = facing;
    if (dir.length > delta * 5)
    {
      if (dir.y < 0)
      {
        if (dir.x < 0) facing = LEFT;
        else facing = RIGHT;
      } else
      {
        if (dir.x < 0 && fabs(dir.x) > dir.y) facing = LEFT;
        else if (dir.x > 0 && fabs(dir.x) > dir.y) facing = RIGHT;
        else facing = FRONT;
      }
    }

    if (facing == LEFT)
    {
      currentImage.y = 0;
      currentImage.x = slide % 8;
    }
    if (facing == RIGHT)
    {
      currentImage.y = 2;
      currentImage.x = slide % 8;
    }
    if (facing == FRONT)
    {
      currentImage.y = 4;
      currentImage.x = 4 + slide % 4;
    }

    if (slide == 7)
      slide = 0;
    else
      slide++;

    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
    totalTime = 0.0f;
  }

  sprite.setTextureRect(uvRect);
  sprite.setPosition(sreep->get_position().x, sreep->get_position().y);
  sprite.setScale(2.25, 2.25);
  prev_pos = sreep->get_position();
}
