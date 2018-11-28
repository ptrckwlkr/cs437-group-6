#include "EntityManager.h"    
        

//returns an instance of event manager
EntityManager* EntityManager::Instance(){
    static EntityManager instance;
    return &instance;
}

void EntityManager::removeEntity(long long entity_id){

    //iterator 
    std::vector<std::shared_ptr<Entity> >::iterator iter = entities.begin();

    while (iter != entities.end()){

        //find the correct entity
        if ( (*iter)->id == entity_id){

            //delete the entity from vector 
            iter = entities.erase(iter);

            //delete from the correct list
        }
        else {
            iter++;
            }
        }
}


//returns entity with the given id 
std::shared_ptr<Entity> &EntityManager::getEntity(long long id){

    //iterator
    std::vector<std::shared_ptr<Entity> >::iterator iter = entities.begin();

    while (iter != entities.end()){

        //find the correct entity with specific type
        if ((*iter)->id == id) {
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
}

void EntityManager::Shutdown(){

}