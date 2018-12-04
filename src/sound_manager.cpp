#include "sound_manager.h"
#include <random>

SoundManager::SoundManager()
{
  EventManager::Instance().registerListener(EventEntityDestroyed::eventType, this, & SoundManager::handleEntityDestroyed);
  EventManager::Instance().registerListener(EventEntityDamaged::eventType, this, & SoundManager::handleEntityDamaged);
  EventManager::Instance().registerListener(EventGoldCollection::eventType, this, & SoundManager::handleGoldCollection);
  EventManager::Instance().registerListener(EventProjectileFired::eventType, this, & SoundManager::handleProjectileFired);
  EventManager::Instance().registerListener(EventMeleeAttack::eventType, this, & SoundManager::handleMeleeAttack);
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
	} else if (event.getType() == Ghost::entityType) {
		float randPitch =((float)(rand() % 401) - 200) / 1000;
		this->ghstDthSound = resources.GetSound("ghostdisappate");
		this->ghstDthSound.setVolume(70.0);
		this->ghstDthSound.setPitch(1 + randPitch);
		this->ghstDthSound.play();
	}
}

void SoundManager::handleEntityDamaged(const EventEntityDamaged &event)
{
	if (event.getEntityType() == Skeleton::entityType) {
		this->skelDmgSound[curSkelDmgSound] = resources.GetSound("bonebreak");
		this->skelDmgSound[curSkelDmgSound].setVolume(60.0);
		this->skelDmgSound[curSkelDmgSound].play();
		curSkelDmgSound = (curSkelDmgSound + 1) % 10;
	} else if (event.getEntityType() == Ghost::entityType) {
		float randPitch =((float)(rand() % 401) - 200) / 1000;
		this->ghstDmgSound[curGhstDmgSound] = resources.GetSound("ghosthiss");
		this->ghstDmgSound[curGhstDmgSound].setVolume(40.0);
		this->ghstDmgSound[curGhstDmgSound].play();
		this->ghstDmgSound[curGhstDmgSound].setPitch(1 + randPitch);
		this->ghstDmgSound[curGhstDmgSound].play();
		curGhstDmgSound = (curGhstDmgSound + 1) % 10;
	}
}

void SoundManager::handleGoldCollection(const EventGoldCollection &event)
{
	float randPitch =((float)(rand() % 401) - 200) / 1000;
	this->coinSound = resources.GetSound("coins");
	this->coinSound.setVolume(50.0);
	this->coinSound.setPitch(1 + randPitch);
	this->coinSound.play();
}

void SoundManager::handleProjectileFired(const EventProjectileFired &event)
{
		this->spellSound[curSpellSound] = resources.GetSound("fireball");
		this->spellSound[curSpellSound].setVolume(50.0);
		this->spellSound[curSpellSound].play();
		curSpellSound = (curSpellSound + 1) % 10;
}

void SoundManager::handleMeleeAttack(const EventMeleeAttack &event)
{
	float randPitch =((float)(rand() % 401) - 200) / 1000;
	this->meleeSound = resources.GetSound("swordswing");
	this->meleeSound.setVolume(50.0);
	this->meleeSound.setPitch(1 + randPitch);
	this->meleeSound.play();
}
