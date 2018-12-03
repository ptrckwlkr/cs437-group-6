#include "EntityManager.h"
#include "entities/Projectile.h"
#include "entities/skeleton.h"
#include "entities/blood.h"

Skeleton::Skeleton(float x, float y) : Entity(x, y, SKELETON_SIZE) {
    obstructible = true;
    hostile = true;

    std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("enemies");
    buffer = resources.GetXMLBuffer("enemies");
    root_node = (*doc).first_node("Root");

    //uses normal skeleton by default
    setType("white");

    EventManager::Instance().registerListener(EventCollision::eventType, this, & Skeleton::handleCollision);
}

void Skeleton::handleCollision(const EventCollision &event)
{
    if (event.getSelf().id == id && event.getOther().getEntityType() == Projectile::entityType)
    {
        health -= 3;
        if (health <= 0) {
            EntityManager::Instance().removeEntity(id);
            EntityManager::Instance().createEntity<Blood>(pos.x, pos.y);
        }
	EventEntityDamaged postDamaged = EventEntityDamaged(id, entityType);
	EventManager::Instance().sendEvent(postDamaged);
    }
}

void Skeleton::updateAttributes() {
    rapidxml::xml_node<> *main_node = root_node->first_node(type.c_str());
    health = std::stoi(main_node->first_node("health")->value());
    speed = std::stoi(main_node->first_node("speed")->value());
    aggro_dist = std::stoi(main_node->first_node("aggro-dist")->value());
}

void Skeleton::setType(std::string param_type) {
    type.assign("skeleton-" + param_type);
    updateAttributes();
}
