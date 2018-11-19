#ifndef CSCI437_ENTITYMANAGER_H
#define CSCI437_ENTITYMANAGER_H

#include <typeinfo>
#include <vector>
#include <map>
#include <list>
#include "entity.h"
#include "Player.h"
//#include "view_manager.h"


class EntityManager{

    private:
        //std::multimap< enum EntityType, Entity > allEntities;
        EntityManager() {};
       ~ EntityManager(){this->Shutdown();}
       std::vector<std::shared_ptr<Entity> > entities;
       std::shared_ptr<Player> player;

    public:
        static EntityManager* Instance();
        void set_player(std::shared_ptr<Player> p) {player = p;}
        void removeEntity(long long entity_id);
        std::shared_ptr<Player> &getPlayer(){return player;}
        std::shared_ptr<Entity> &getEntity(enum EntityType type);
        std::shared_ptr<Entity> &getEntity(long long id);
        std::vector<std::shared_ptr<Entity>> &getEntites() {return entities;}
        void ClearAll();
        void Shutdown();

        template <class T>
        std::shared_ptr<T> createEntity(float x, float y)
        {
            std::shared_ptr<T> entity = std::make_shared<T>(x, y);
            entities.push_back(entity);
//            ViewManager::Instance()->add_view(entity);
            return entity;
        }

        template <class T>
        std::vector<std::shared_ptr<T>> getEntitiesByType()
        {
          std::shared_ptr<T> ptr;
          std::vector<std::shared_ptr<T>> type_entities;
          for (auto &entity : entities)
          {
            if (ptr = std::dynamic_pointer_cast<T>(entity))
            {
              type_entities.push_back(ptr);
            }
          }
          return type_entities;
        }
};

#endif //CSCI437_ENTITYMANAGER_