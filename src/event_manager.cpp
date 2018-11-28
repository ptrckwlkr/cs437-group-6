#include "EventManager.h"

// returns an instance of event manager
EventManager* EventManager::Instance(){
  static EventManager instance;
  return &instance;
}

void EventManager::shutdown()
{
  clearEvents();
  processUnregisters();
}

void EventManager::processEvents()
{
  std::swap(queueActive, queueInactive);
  while (!queueActive.empty())
  {
    dispatchEvent(*queueActive.front());
    //then remove from the list
    queueActive.pop();
  }
  processUnregisters();
}

void EventManager::unregisterObject(EventType type, Entity *entity)
{
  auto range = database.equal_range(type);
  for (auto i = range.first; i != range.second; ++i){
    if ((*i).second.first->id == entity->id)
    {
      erasures.push(i);
      //i = database.erase(i);
      return;
    }
  }
}

void EventManager::unregisterAll(Entity *entity)
{
  auto i = database.begin();
  while (i != database.end())
  {
    if ((*i).second.first->id == entity->id)
    {
      i = database.erase(i);
    }
    else i++;
  }
}

bool EventManager::alreadyRegistered(EventType type, Entity *entity)
{
  //all objects that receive this event
  auto range = database.equal_range(type);
  for (auto i = range.first; i != range.second; ++i)
  {
    //if object already subscribed
    if((*i).second.first->id == entity->id){
      return true;
    }
  }
  return false;
}

void EventManager::processUnregisters()
{
  while (!erasures.empty())
  {
    auto i = erasures.front();
    database.erase(i);
    erasures.pop();
  }
}

void EventManager::dispatchEvent(Event &event)
{
  auto type = event.getEventType();
  auto range = database.equal_range(type);
  for (auto i = range.first; i != range.second; ++i)
  {
    auto entity = (*i).second.first;
    auto callback = (*i).second.second;
    (entity->*callback)(event);
  }
}

void EventManager::clearEvents()
{
  std::queue<std::shared_ptr<Event>> empty1;
  std::queue<std::shared_ptr<Event>> empty2;
  std::swap(queueActive, empty1);
  std::swap(queueInactive, empty1);
}
