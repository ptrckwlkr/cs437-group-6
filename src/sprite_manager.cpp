#include <events/event_entity_destroyed.h>
#include "sprite_manager.h"

SpriteManager &SpriteManager::Instance(){
  static SpriteManager instance;
  return instance;
}

SpriteManager::SpriteManager()
{
  EventManager::Instance()->registerListener(EventEntityDestroyed::eventType, this, & SpriteManager::handleEntityRemoval);
  EventManager::Instance()->registerListener(EventEntityCreated::eventType, this, & SpriteManager::handleEntityCreation);
}

SpriteManager::~SpriteManager()
{
  EventManager::Instance()->unregisterAll(this);
  animations.clear();
}

void SpriteManager::updateAnimations(float delta)
{
  for (auto &animation : animations)
  {
    animation.second->update(delta);
  }
}

void SpriteManager::handleEntityRemoval(const EventEntityDestroyed &event)
{
  auto i = animations.find(event.getEntityID());
  if (i != animations.end()) {
    animations.erase(i);
  }
}

void SpriteManager::handleEntityCreation(const EventEntityCreated &event)
{
  auto animation = AnimationFactory::createAnimation(&event.getEntity());
  if (animation) {
    animations.insert(std::pair<long long, std::shared_ptr<Animation>>(event.getEntity().id, animation));
  }
}
