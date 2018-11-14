#include "EntityManager.h"    
        

//returns an instance of event manager
EntityManager* EntityManager::Instance(){
    static EntityManager instance;
    return &instance;
}

void EntityManager::addEntity(std::shared_ptr<Entity> e){
    entities.push_back(e);
}

void EntityManager::removeEntity(std::shared_ptr<Entity> e){

    //iterator 
    std::vector<std::shared_ptr<Entity> >::iterator iter = entities.begin();

    while (iter != entities.end()){

        //find the correct entity
        if ( (*iter) == e){

            //delete the entity
            iter = entities.erase(iter);
        }

        else{
            iter++;
        }
    }
}

std::shared_ptr<Entity> EntityManager::getEntity(enum EntityType type){
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

void EntityManager::Shutdown(){

}