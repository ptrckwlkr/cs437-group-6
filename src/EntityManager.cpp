#include <unordered_map>
#include "events/event_entity_destroyed.h"
#include "EntityManager.h"

//returns an instance of event manager
EntityManager* EntityManager::Instance(){
    static EntityManager instance;
    return &instance;
}

void EntityManager::removeEntity(long long entity_id)
{
    auto i = entity_set.find(entity_id);
    if (i != entity_set.end())
    {
        auto entity = i->second;
        EventEntityDestroyed event(entity->id, entity->getEntityType(), entity->get_position());
        EventManager::Instance()->sendEvent(event);
        entity_set.erase(i);
    }
}


//returns entity with the given id 
std::shared_ptr<Entity> &EntityManager::getEntity(long long entity_id)
{
    return entity_set[entity_id];
}


void EntityManager::reset()
{
    for (auto &i : entity_set)
    {
      auto e = i.second;
      EventManager::Instance()->unregisterAll(e.get());
    }
    EventManager::Instance()->unregisterAll(player.get());
    entity_set.clear();
}
