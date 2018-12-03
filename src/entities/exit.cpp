#include "events/event_exit_reached.h"
#include "entities/exit.h"
#include "entities/Player.h"

Exit::Exit(float x, float y) : Entity(x, y, EXIT_SIZE)
{
  EventManager::Instance().registerListener(EventCollision::eventType, this, &Exit::handleCollision);
}

void Exit::handleCollision(const EventCollision &event)
{
  if (event.getSelf().id == id && event.getOther().getEntityType() == Player::entityType)
  {
    printf("EventExitReached event dispatched\n");
    EventExitReached e;
    EventManager::Instance().sendEvent(e);
  }
}
