#include "sound_manager.h"
#include <random>

SoundManager::SoundManager()
{
  EventManager::Instance().registerListener(EventEntityDestroyed::eventType, this, & SoundManager::handleEntityDestroyed);
  EventManager::Instance().registerListener(EventEntityDamaged::eventType, this, & SoundManager::handleEntityDamaged);
  EventManager::Instance().registerListener(EventGoldCollection::eventType, this, & SoundManager::handleGoldCollection);
  EventManager::Instance().registerListener(EventProjectileFired::eventType, this, & SoundManager::handleProjectileFired);
}

SoundManager::~SoundManager()
{
  EventManager::Instance().unregisterAll(this);
}

void SoundManager::handleEntityDestroyed(const EventEntityDestroyed &event)
{
	if (event.getType() == Skeleton::entityType) {
		float randPitch =((float)(rand() % 401) - 200) / 1000;
		this->skelDthSound = resources.GetSound("monsterdeath");
		this->skelDthSound.setVolume(70.0);
		this->skelDthSound.setPitch(1 + randPitch);
		this->skelDthSound.play();
	}
}

void SoundManager::handleEntityDamaged(const EventEntityDamaged &event)
{
	if (event.getType() == Skeleton::entityType) {
		this->skelDmgSound[curSkelDmgSound] = resources.GetSound("bonebreak");
		this->skelDmgSound[curSkelDmgSound].setVolume(70.0);
		this->skelDmgSound[curSkelDmgSound].play();
		curSkelDmgSound = (curSkelDmgSound + 1) % 10;
	}
}

void SoundManager::handleGoldCollection(const EventGoldCollection &event)
{
	float randPitch =((float)(rand() % 401) - 200) / 1000;
	this->coinSound = resources.GetSound("coins");
	this->coinSound.setVolume(70.0);
	this->coinSound.setPitch(1 + randPitch);
	this->coinSound.play();
}

void SoundManager::handleProjectileFired(const EventProjectileFired &event)
{
		this->spellSound[curSpellSound] = resources.GetSound("fireball");
		this->spellSound[curSpellSound].setVolume(70.0);
		this->spellSound[curSpellSound].play();
		curSpellSound = (curSpellSound + 1) % 10;
}
