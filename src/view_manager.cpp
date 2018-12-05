#include "view_manager.h"

void ViewManager::init(GameLogic *s)
{
  state = s;
  EventManager::Instance().registerListener(EventEntityDestroyed::eventType, this, & ViewManager::handleEntityRemoval);
  EventManager::Instance().registerListener(EventEntityCreated::eventType, this, & ViewManager::handleEntityCreation);
}

ViewManager &ViewManager::Instance()
{
  static ViewManager instance;
  return instance;
}

void ViewManager::handleEntityRemoval(const EventEntityDestroyed &event)
{
  auto i = views.find(event.getEntityID());
  if (i != views.end()) views.erase(i);
}

void ViewManager::update_views(float delta)
{
  for (auto &view : views)
  {
    view.second->update(delta);
  }
}

void ViewManager::update_player_view(float delta)
{
  curr_player_view = view_switch;
  curr_player_view->update(delta);
}

View &ViewManager::get_view(long long entity_id)
{
  return *views[entity_id];
}

void ViewManager::handleEntityCreation(const EventEntityCreated &event)
{
  auto view = ViewFactory::createView(state, &event.getEntity());
  if (view) views.insert(std::pair<long long, std::shared_ptr<View>>(event.getEntity().id, view));
}
