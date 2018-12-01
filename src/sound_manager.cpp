#include "sound_manager.h"
#include <random>

SoundManager::SoundManager()
{
  EventManager::Instance()->registerListener(EventEntityDestroyed::eventType, this, & SoundManager::handleEntityDestroyed);
  EventManager::Instance()->registerListener(EventEntityDamaged::eventType, this, & SoundManager::handleEntityDamaged);
  EventManager::Instance()->registerListener(EventGoldCollection::eventType, this, & SoundManager::handleGoldCollection);
}

SoundManager::~SoundManager()
{
  EventManager::Instance()->unregisterAll(this);
}

void SoundManager::handleEntityDestroyed(const EventEntityDestroyed &event)
{

}

void SoundManager::handleEntityDamaged(const EventEntityDamaged &event)
{
	if (event.getType() == Skeleton::entityType) {
		this->curSound = resources.GetSound("bonebreak");
		this->curSound.setVolume(70.0);
		this->curSound.play();
	}
}

void SoundManager::handleGoldCollection(const EventGoldCollection &event)
{
	float randPitch =((float)(rand() % 401) - 200) / 1000;
	this->curSound = resources.GetSound("coins");
	this->curSound.setVolume(70.0);
	this->curSound.setPitch(1 + randPitch);
	this->curSound.play();
}
