#include "view_manager.h"

void ViewManager::init(GameLogic *s)
{
  state = s;
  EventManager::Instance()->registerListener(EventEntityDestroyed::eventType, this, &handleEntityRemoval);
  EventManager::Instance()->registerListener(EventEntityCreated::eventType, this, &handleEntityCreation);
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

void ViewManager::handleEntityCreation(const EventEntityCreated &event)
{
  auto view = ViewFactory::createView(state, &event.getEntity());
  if (view) views.insert(std::pair<long long, std::shared_ptr<View>>(event.getEntity().id, view));
}
