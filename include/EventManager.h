#ifndef CSCI437_EVENTMANAGER_H
#define CSCI437_EVENTMANAGER_H

#include <SFML/Window/Event.hpp>
#include <list>
#include <map>
#include <memory>
#include <functional>
#include <events/event_gold_collection.h>
#include <queue>
#include "event.h"
#include "entity.h"

typedef void (Entity::* Callback)(const Event&);

class EventManager
{

public:
    //returns an instance of event manager
    static EventManager* Instance();

    void shutdown();
    void processEvents();
    void unregisterObject(EventType type, Entity *entity);
    void unregisterAll(Entity *entity);

    template <class T>
    void sendEvent(T &event)
    {
      queueInactive.push(std::make_shared<T>(event));
    }

    template <class T, typename U>
    void registerEntity(EventType type, T *entity, U callback)
    {
      if (!entity || alreadyRegistered(type, entity)) return;
      Callback c = (Callback)callback;
      database.insert(std::make_pair(type, std::make_pair(entity, c)));
    };

private:
    EventManager() = default;;
    ~EventManager() = default;
    bool alreadyRegistered(EventType type, Entity *entity);
    void processUnregisters();
    void dispatchEvent(Event &event);
    void clearEvents();

    // list of events that need to be processed
    std::queue<std::shared_ptr<Event>> queueActive;
    std::queue<std::shared_ptr<Event>> queueInactive;
    std::multimap<EventType, std::pair<Entity*, Callback>> database;

    std::queue<std::multimap<EventType, std::pair<Entity*, Callback>>::iterator> erasures;

};

#endif //CSCI437_EVENTMANAGER_H