#ifndef CSCI437_VIEW_FACTORY_H
#define CSCI437_VIEW_FACTORY_H

#include <memory>
#include <unordered_map>
#include "view.h"
#include "game_logic.h"

typedef std::shared_ptr<View> (* Factory)(GameLogic*, Entity&);

template<class E, class V>
std::shared_ptr<View> createInstance(GameLogic *state, E &entity)
{
  return std::make_shared<V>(state, entity);
}

class ViewManager;
class ViewFactory
{
    friend class ViewManager;

private:
    void init(GameLogic *s) {state = s;}
    std::shared_ptr<View> createView(Entity *entity)
    {
      std::shared_ptr<View> view = nullptr;
      auto i = map.find(entity->getEntityType());
      if (i != map.end())
      {
        Factory f = i->second;
        view = f(state, *entity);
      }
      return view;
    }
    ViewFactory();
    GameLogic *state = nullptr;
    std::unordered_map<EntityType, Factory> map;

};

#endif //CSCI437_VIEW_FACTORY_H
