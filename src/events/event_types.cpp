#include "events/event_collision.h"
#include "events/event_entity_created.h"
#include "events/event_cycle_complete.h"
#include "events/event_entity_damaged.h"
#include "events/event_entity_destroyed.h"
#include "events/event_exit_reached.h"
#include "events/event_level_complete.h"
#include "events/event_player_died.h"
#include "events/event_projectile_fired.h"
#include "events/event_wall_collision.h"
#include "events/event_victory.h"
#include "events/event_melee_attack.h"

const EventType EventCollision::eventType         = (EventType)(&EventCollision::eventType);
const EventType EventEntityCreated::eventType     = (EventType)(&EventEntityCreated::eventType);
const EventType EventCycleComplete::eventType     = (EventType)(&EventCycleComplete::eventType);
const EventType EventEntityDamaged::eventType     = (EventType)(&EventEntityDamaged::eventType);
const EventType EventEntityDestroyed::eventType   = (EventType)(&EventEntityDestroyed::eventType);
const EventType EventExitReached::eventType       = (EventType)(&EventExitReached::eventType);
const EventType EventGoldCollection::eventType    = (EventType)(&EventGoldCollection::eventType);
const EventType EventLevelComplete::eventType     = (EventType)(&EventLevelComplete::eventType);
const EventType EventPlayerDied::eventType        = (EventType)(&EventPlayerDied::eventType);
const EventType EventProjectileFired::eventType   = (EventType)(&EventProjectileFired::eventType);
const EventType EventWallCollision::eventType     = (EventType)(&EventWallCollision::eventType);
const EventType EventMeleeAttack::eventType	      = (EventType)(&EventMeleeAttack::eventType);
const EventType EventVictory::eventType	          = (EventType)(&EventVictory::eventType);
