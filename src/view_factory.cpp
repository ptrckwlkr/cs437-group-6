#include "views/view_projectile.h"
#include "views/view_skeleton.h"
#include "view_factory.h"

ViewFactory::ViewFactory()
{
  map.insert(std::make_pair(Skeleton::entityType, (Factory)createInstance<Skeleton, SkeletonView>));
  map.insert(std::make_pair(Projectile::entityType, (Factory)createInstance<Projectile, ProjectileView>));
}
