#ifndef CSCI437_SPRITE_MANAGER_H
#define CSCI437_SPRITE_MANAGER_H


#include <unordered_map>
#include "events/event_entity_created.h"
#include "events/event_entity_destroyed.h"
#include "listener.h"
#include "Animations/Animation.h"
#include "animation_factory.h"

class SpriteManager : public Listener
{

public:
    SpriteManager();
    ~SpriteManager();
    Animation &getAnimation(long long entity_id) {return *animations[entity_id];}
    void updateAnimations(float delta);
    const std::unordered_map<long long int, std::shared_ptr<Animation>> &getAnimations() const {return animations;}


private:
    std::unordered_map<long long, std::shared_ptr<Animation>> animations;
    void handleEntityRemoval(const EventEntityDestroyed &event);
    void handleEntityCreation(const EventEntityCreated &event);

};


#endif //CSCI437_SPRITE_MANAGER_H
