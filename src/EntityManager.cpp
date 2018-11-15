#include "EntityManager.h"    
        

//returns an instance of event manager
EntityManager* EntityManager::Instance(){
    static EntityManager instance;
    return &instance;
}

void EntityManager::createEntity(EntityType type, int x, int y, int s)
{
    switch (type)
    {
        case TYPE_PROJECTILE:
        {
            std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(x, y, s);
            projectiles.push_back(projectile);
            entities.push_back(projectile);
        }
            break;
        case TYPE_GOLD:
        {
            std::shared_ptr<Gold> gold = std::make_shared<Gold>(x, y);
            golds.push_back(gold);
            entities.push_back(gold);
        }
            break;
        case TYPE_SKELETON:
        {
            std::shared_ptr<Skeleton> skel = std::make_shared<Skeleton>(x, y);
            skeletons.push_back(skel);
            entities.push_back(skel);
        }
            break;

        case TYPE_PLAYER:
            player = std::make_shared<Player>(x, y, s);
            entities.push_back(player);
            break;
    }  
}
void EntityManager::removeEntity(std::shared_ptr<Entity> e){

    //iterator 
    std::vector<std::shared_ptr<Entity> >::iterator iter = entities.begin();

    while (iter != entities.end()){

        //find the correct entity
        if ( (*iter) == e){

            //delete the entity from vector 
            iter = entities.erase(iter);

            //delete from the correct list
            //problem of deleteing entity from specific list
        }
        else {
            iter++;
            }
        }
}

//Running into problems of changing entity to projectile to place in list 

// std::list<std::shared_ptr<Projectile>> EntityManager::getProjectiles(){
//     std::vector<std::shared_ptr<Entity> >::iterator iter = entities.begin();

//     while (iter != entities.end()){

//         //find the projectile base on type
//         if ( (*iter)->get_type() == TYPE_PROJECTILE){
//             //add to list 
//             return projectiles.push_back(iter);
//         }

//         else{
//             iter++;
//         }
//     }

// }

//returns entity with the given id 
std::shared_ptr<Entity> &EntityManager::getEntity(long long id){

    //iterator
    std::vector<std::shared_ptr<Entity> >::iterator iter = entities.begin();

    while (iter != entities.end()){

        //find the correct entity with specific type
        if ((*iter)->get_id() == id) {
            //return entity 
            return (*iter);
        }

        else{
            iter++;
        }
    }

}

std::shared_ptr<Entity> &EntityManager::getEntity(enum EntityType type){
     //iterator
    std::vector<std::shared_ptr<Entity> >::iterator iter = entities.begin();

    while (iter != entities.end()){

        //find the correct entity with specific type
        if ( (*iter)->get_type() == type){
            //return entity 
            return (*iter);
        }

        else{
            iter++;
        }
    }
}


void EntityManager::ClearAll(){
    entities.clear();
    projectiles.clear();
    golds.clear();
    skeletons.clear();
    entities.clear();
}

void EntityManager::Shutdown(){

}