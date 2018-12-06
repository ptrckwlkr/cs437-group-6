#include "entities/potion.h"
#include "EntityManager.h"


Potion::Potion(float x, float y) : Entity(x, y, POTION_SIZE)
{
    EventManager::Instance().registerListener(EventCollision::eventType, this, &Potion::handleCollision);
    //represents type of potion and index in texture file, 0 for health, 1 for mana, 2 for both
    type_num = rand() % 3;
}




void Potion::handleCollision(const EventCollision &event)
{
    if (event.getSelf().id == id && event.getOther().getEntityType() == Player::entityType)
    {
        if (type_num == 0 || type_num == 2) {
            float health = EntityManager::Instance().getPlayer()->get_health();
            //sets player health to current health + 25% of max health or max health if necessary
            if ((health + EntityManager::Instance().getPlayer()->get_max_health()/4) < EntityManager::Instance().getPlayer()->get_max_health())
                EntityManager::Instance().getPlayer()->set_health(health + EntityManager::Instance().getPlayer()->get_max_health()/4);
            else
                EntityManager::Instance().getPlayer()->set_health(EntityManager::Instance().getPlayer()->get_max_health());
        }

        if (type_num == 1 || type_num == 2) {
            //because mana regens this will just fill the mana
            EntityManager::Instance().getPlayer()->set_mana(EntityManager::Instance().getPlayer()->get_max_mana());
        }


        EntityManager::Instance().removeEntity(id);
    }
}