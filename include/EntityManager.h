#ifndef CSCI437_ENTITYMANAGER_H
#define CSCI437_ENTITYMANAGER_H

#include <vector>
#include <map>
#include "entity.h"
#include "Player.h"
#include "gold.h"
#include "Projectile.h"
#include "skeleton.h"


class EntityManager{

    private:
        //std::multimap< enum EntityType, Entity > allEntities;
        EntityManager() {};
       ~ EntityManager(){this->Shutdown();}
       std::vector<Player*> players;
       std::vector<Gold*> golds;
       std::vector<Projectile*> projectiles;
       std::vector<Skeleton*> skeletons;

       std::vector<std::shared_ptr<Entity> > entities;

    public:
        static EntityManager* Instance();
        
        void addEntity( std::shared_ptr<Entity> e);
        void removeEntity(std::shared_ptr<Entity> e );
        std::shared_ptr<Entity> getEntity(enum EntityType type);
        std::vector<std::shared_ptr<Entity> > getEntites(){ return entities;}
        void Shutdown();

        //std::vector<std::shared_ptr<Entity> >
        // void addEntity ( enum EntityType, Entity entity);
        // Entity* getEntity(enum EntityType type);
        // void removeEntity ( Entity entity);
        // std::multimap< enum EntityType, Entity> get_Entities(){ return allEntities;}


};
#endif //CSCI437_ENTITYMANAGER_H