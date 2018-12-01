#include "views/view_projectile.h"
#include "views/view_skeleton.h"
#include "views/view_factory.h"

using namespace ViewFactory;

/**
 * Function pointer to a createInstance<EntityType, ViewType> method
 */
typedef std::shared_ptr<View> (*Factory)(GameLogic *, Entity &);

/**
 * View creation method
 *
 * @tparam E:     Entity type
 * @tparam V:     Corresponding view type
 * @param state:  Pointer to the GameLogic
 * @param entity: Pointer to the entity of type E
 * @return        Pointer to the newly created view
 */
template<class E, class V>
const std::shared_ptr<View> createInstance(GameLogic *state, E &entity)
{
  return std::make_shared<V>(state, entity);
}

/**
 * ViewFactory creation method
 *
 * @param state:  Pointer to the game logic
 * @param entity: Pointer to the entity of type E
 * @return:       Pointer to the newly created view, or null if no view exists for entity of type E
 */
std::shared_ptr<View> ViewFactory::createView(GameLogic *state, Entity *entity)
{
  /**
   * The EntityType > ViewType mapping.
   * ADD AN ENTRY WITH AN ENTITY'S CORRESPONDING VIEW TO AUTOMATE VIEW CREATION
   */
  static const std::unordered_map<EntityType, Factory> map {
          {Skeleton::entityType,      (Factory)createInstance<Skeleton, SkeletonView>},
          {Projectile::entityType,    (Factory)createInstance<Projectile, ProjectileView>}
  };

  std::shared_ptr<View> view = nullptr;
  auto i = map.find(entity->getEntityType());
  if (i != map.end())
  {
    Factory f = i->second;
    view = f(state, *entity);
  }
  return view;
}
