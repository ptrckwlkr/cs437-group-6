#ifndef CSCI437_ENTITYMANAGER_H
#define CSCI437_ENTITYMANAGER_H

#include <vector>
#include <map>
#include <list>
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
       std::list<std::shared_ptr<Skeleton> > skeletons;
       std::list<std::shared_ptr<Gold> > golds;
       std::list<std::shared_ptr<Projectile> > projectiles;
       std::vector<std::shared_ptr<Entity> > entities;
       std::shared_ptr<Player> player;

    public:
        static EntityManager* Instance();

        void createEntity( EntityType type, int x, int y, int s);
        void removeEntity(std::shared_ptr<Entity> e );
        std::list<std::shared_ptr<Projectile> > getProjectiles(){return projectiles;}
        std::list<std::shared_ptr<Gold> > getGolds(){return golds;}
        std::list<std::shared_ptr<Skeleton> > getSkeletions(){return skeletons;}
        std::shared_ptr<Player> getPlayer(){return player;}
        std::shared_ptr<Entity> getEntity(enum EntityType type);
        std::shared_ptr<Entity> getEntity(long long id);
        std::vector<std::shared_ptr<Entity> > getEntites(){ return entities;}
        void ClearAll ( );
        void Shutdown();
};

#endif //CSCI437_ENTITYMANAGER_