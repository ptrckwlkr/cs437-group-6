#include "entities/melee.h"
#include "EntityManager.h"
#include "events/event_melee_attack.h"

Melee::Melee(float x, float y) : Entity(x, y, 1)
{
    immovable = true;

    EventMeleeAttack postAttack = EventMeleeAttack(id);
    EventManager::Instance().sendEvent(postAttack);

    EventManager::Instance().registerListener(EventCollision::eventType, this, &Melee::handleCollision);
    EventManager::Instance().registerListener(EventCycleComplete::eventType, this, &Melee::handleCycleComplete);
    sword = EntityManager::Instance().createEntity<Sword>(x, y).get();
}

void Melee::handleCollision(const EventCollision &event)
{
    if (event.getSelf().id == id && event.getOther().is_hostile())
    {
      event.getOther().take_damage(damage);
      Vector2D pushback = event.getOther().get_position() - EntityManager::Instance().getPlayer()->get_position();
      event.getOther().set_position(event.getOther().get_position() + pushback.normal() * 10);
      EventEntityDamaged postDamaged = EventEntityDamaged(event.getOther().id, event.getOther().getEntityType());
      EventManager::Instance().sendEvent(postDamaged);
    }
}

void Melee::setDirection(Vector2D d)
{
    sword->setAngle(d);
}

void Melee::handleCycleComplete(const EventCycleComplete &event)
{
    EntityManager::Instance().removeEntity(id);
}
