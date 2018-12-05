#include <unordered_map>
#include "events/event_entity_destroyed.h"
#include "EntityManager.h"

//returns an instance of event manager
EntityManager &EntityManager::Instance(){
    static EntityManager instance;
    return instance;
}

void EntityManager::removeEntity(long long entity_id)
{
    auto i = entities.find(entity_id);
    if (i != entities.end())
    {
        auto entity = i->second;
        EventEntityDestroyed event(entity->id, entity->getEntityType(), entity->get_position());
        EventManager::Instance().sendEvent(event);
        entities.erase(i);
    }
}


//returns entity with the given id 
std::shared_ptr<Entity> &EntityManager::getEntity(long long entity_id)
{
    return entities[entity_id];
}


void EntityManager::reset()
{
    for (auto &i : entities)
    {
      auto e = i.second;
      EventManager::Instance().unregisterAll(e.get());
    }
    EventManager::Instance().unregisterAll(player.get());
    entities.clear();
}
