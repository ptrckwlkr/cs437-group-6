#ifndef CSCI437_ENTITYMANAGER_H
#define CSCI437_ENTITYMANAGER_H

#include <typeinfo>
#include <unordered_map>
#include <memory>
#include "events/event_entity_created.h"
#include "entities/entity.h"
#include "entities/Player.h"
#include "views/view_manager.h"


class EntityManager{

private:
    EntityManager() = default;
    ~EntityManager() = default;
    std::unordered_map<long long, std::shared_ptr<Entity>> entity_set;
    std::shared_ptr<Player> player;

public:
    static EntityManager &Instance();
    void set_player(std::shared_ptr<Player> p) {player = p;}
    void removeEntity(long long entity_id);
    std::shared_ptr<Player> &getPlayer(){return player;}
    std::shared_ptr<Entity> &getEntity(long long entity_id);
    std::unordered_map<long long, std::shared_ptr<Entity>> &getEntites() {return entity_set;}
    void reset();

    template <class T>
    std::shared_ptr<T> createEntity(float x, float y)
    {
        std::shared_ptr<T> entity = std::make_shared<T>(x, y);
        std::shared_ptr<Entity> ent = entity;
        entity_set.insert(std::pair<long long, std::shared_ptr<Entity>>(ent->id, entity));
        EventEntityCreated event(entity.get());
        EventManager::Instance().sendEvent(event);
        return entity;
    }

    template <class T>
    std::vector<std::shared_ptr<T>> getEntitiesByType()
    {
      std::shared_ptr<T> ptr;
      std::vector<std::shared_ptr<T>> type_entities;
      for (auto &i : entity_set)
      {
        auto entity = i.second;
        if (ptr = std::dynamic_pointer_cast<T>(entity))
        {
          type_entities.push_back(ptr);
        }
      }
      return type_entities;
    }
};

#endif //CSCI437_ENTITYMANAGER_