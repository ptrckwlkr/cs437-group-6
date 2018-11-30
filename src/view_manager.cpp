#include "view_manager.h"

void ViewManager::init(GameLogic *s)
{
  state = s;
  factory.init(s);
  EventManager::Instance()->registerListener(EventEntityDestroyed::eventType, this, &handleEntityRemoval);
}

ViewManager *ViewManager::Instance()
{
  static ViewManager instance;
  return &instance;
}

void ViewManager::handleEntityRemoval(const EventEntityDestroyed &event)
{
  views.erase(event.getEntityID());
}

void ViewManager::update_views(float delta)
{
  curr_player_view->update(delta);
  for (auto &view : views)
  {
    view.second->update(delta);
  }
}

View &ViewManager::get_view(long long entity_id)
{
  return *views[entity_id];
}

std::vector<std::shared_ptr<View>> ViewManager::get_views()
{
  std::vector<std::shared_ptr<View>> view_list;
  for(auto kv : views) view_list.push_back(kv.second);
  return view_list;
}
