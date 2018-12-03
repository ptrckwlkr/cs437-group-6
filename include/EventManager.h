#ifndef CSCI437_EVENTMANAGER_H
#define CSCI437_EVENTMANAGER_H

#include <SFML/Window/Event.hpp>
#include <list>
#include <map>
#include <memory>
#include <functional>
#include <events/event_gold_collection.h>
#include <queue>
#include "events/event.h"
#include "listener.h"

typedef void (Listener::* Callback)(const Event&);

class EventManager
{

public:
    //returns an instance of event manager
    static EventManager &Instance();

    void reset();
    void processEvents();
    void unregisterListener(EventType type, Listener *listener);
    void unregisterAll(Listener *listener);

    template <class T>
    void sendEvent(T &event)
    {
      queueInactive.push(std::make_shared<T>(event));
    }

    template <class T, typename U>
    void registerListener(EventType type, T *listener, U callback)
    {
      if (!listener || alreadyRegistered(type, listener)) return;
      Callback c = (Callback)callback;
      database.insert(std::make_pair(type, std::make_pair(listener, c)));
    };

private:
    EventManager() = default;;
    ~EventManager() = default;
    bool alreadyRegistered(EventType type, Listener *listener);
    void processUnregisters();
    void dispatchEvent(Event &event);
    void clearEvents();

    // list of events that need to be processed
    std::queue<std::shared_ptr<Event>> queueActive;
    std::queue<std::shared_ptr<Event>> queueInactive;
    std::multimap<EventType, std::pair<Listener*, Callback>> database;

    std::queue<std::multimap<EventType, std::pair<Listener*, Callback>>::iterator> erasures;

};

#endif //CSCI437_EVENTMANAGER_H