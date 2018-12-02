#include "entities/entity.h"
#include "entities/blood.h"
#include "entities/exit.h"
#include "entities/gold.h"
#include "entities/Player.h"
#include "entities/Projectile.h"
#include "entities/skeleton.h"

const EntityType Blood::entityType        = (EntityType)(&Blood::entityType);
const EntityType Exit::entityType         = (EntityType)(&Exit::entityType);
const EntityType Gold::entityType         = (EntityType)(&Gold::entityType);
const EntityType Player::entityType       = (EntityType)(&Player::entityType);
const EntityType Projectile::entityType   = (EntityType)(&Projectile::entityType);
const EntityType Skeleton::entityType     = (EntityType)(&Skeleton::entityType);
