#include "EventManager.h"

// returns an instance of event manager
EventManager* EventManager::Instance(){
  static EventManager instance;
  return &instance;
}

void EventManager::reset()
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

void EventManager::unregisterListener(EventType type, Listener *listener)
{
  auto range = database.equal_range(type);
  for (auto i = range.first; i != range.second; ++i){
    if ((*i).second.first == listener)
    {
      erasures.push(i);
      //i = database.erase(i);
      return;
    }
  }
}

void EventManager::unregisterAll(Listener *listener)
{
  auto i = database.begin();
  while (i != database.end())
  {
    if ((*i).second.first == listener)
    {
      i = database.erase(i);
    }
    else i++;
  }
}

bool EventManager::alreadyRegistered(EventType type, Listener *listener)
{
  //all objects that receive this event
  auto range = database.equal_range(type);
  for (auto i = range.first; i != range.second; ++i)
  {
    //if object already subscribed
    if((*i).second.first == listener){
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
    auto listener = (*i).second.first;
    auto callback = (*i).second.second;
    (listener->*callback)(event);
  }
}

void EventManager::clearEvents()
{
  std::queue<std::shared_ptr<Event>> empty1;
  std::queue<std::shared_ptr<Event>> empty2;
  std::swap(queueActive, empty1);
  std::swap(queueInactive, empty1);
}
