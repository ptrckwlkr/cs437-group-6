#ifndef CSCI437_SOUND_MANAGER_H
#define CSCI437_SOUND_MANAGER_H

#include <unordered_map>
#include "events/event_entity_destroyed.h"
#include "events/event_entity_damaged.h"
#include "events/event_gold_collection.h"
#include "events/event_projectile_fired.h"
#include <SFML/Audio.hpp>
#include "listener.h"
#include "entities/skeleton.h"

class SoundManager : public Listener
{

public:
    SoundManager();
    ~SoundManager();

private:
    sf::Sound coinSound;
    sf::Sound skelDmgSound[10];
    int curSkelDmgSound = 0;
    sf::Sound skelDthSound;
    sf::Sound spellSound[10];
    int curSpellSound = 0;

    void handleEntityDamaged(const EventEntityDamaged &event);
    void handleEntityDestroyed(const EventEntityDestroyed &event);
    void handleGoldCollection(const EventGoldCollection &event);
    void handleProjectileFired(const EventProjectileFired &event);

};


#endif //CSCI437_SOUND_MANAGER_H