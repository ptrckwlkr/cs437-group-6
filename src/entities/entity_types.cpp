#include "entities/entity.h"
#include "entities/gold.h"
#include "entities/Player.h"
#include "entities/Projectile.h"
#include "entities/skeleton.h"

const EntityType Gold::entityType         = (EntityType)(&Gold::entityType);
const EntityType Player::entityType       = (EntityType)(&Player::entityType);
const EntityType Projectile::entityType   = (EntityType)(&Projectile::entityType);
const EntityType Skeleton::entityType     = (EntityType)(&Skeleton::entityType);
