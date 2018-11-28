#ifndef CSCI437_EVENTMANAGER_H
#define CSCI437_EVENTMANAGER_H

#include <SFML/Window/Event.hpp>
#include <list>
#include <map>
#include <memory>
#include <functional>
#include <events/event_gold_collection.h>
#include "event.h"
#include "entity.h"

typedef std::pair<Entity*, void*> EventDelegate;
typedef void (Entity::* Callback)(const Event&);

class Delegate
{
public:
    void (Entity::* callback)(Event&);
};

class EventManager
{
private:
    //stores objects and their events
    std::multimap<EVENTID, Entity*> db;

    //list of events that need to be processed
    std::list<std::shared_ptr<Event>> currentEvents;

    EventManager() {};
    ~EventManager() { this->Shutdown(); }

    //copies constructor
    // EventManager( const EventManager& rhs){};
    // EventManager& operator = ( const EventManager& rhs){};

    //helper
    bool AlreadyRegistered( EVENTID event, Entity* object);

    //will dispatch events
    void DispactchEvent(Event &event);

    std::multimap<EventType, std::pair<Entity*, Callback>> database;

public:

    //returns an instance of event manager
    static EventManager* Instance();

    //register object to listen to for an event
    void RegisterObject(EVENTID event, Entity* object);

    //unregister object from an event
    void UnregisterObject( EVENTID event , Entity* object);

    //unregister object from all event
    void UnregisterAll(Entity* object );

    //send event
    void SendEvent(EVENTID event, void* data = 0);

    void ProcessEvents();

    void ClearEvents();

    //shuts down the event manager
    void Shutdown();


    /*
    void registerEvent(EventType e, Entity* entity, void* callback)
    {
      auto x = EventGoldCollection(nullptr);
      (entity->((Entity::*)callback))(x);
      //database.insert(std::make_pair(e, obj));

      //EventDelegate d = std::pair<Entity *, void *>(obj, callback);
    }*/


    //void send(Event &event);
    void unregister(EventType e, Entity *obj);
    void process();
    void dispatch(Event &event);

    template <class T>
    void send(T event)
    {
      currentEvents.push_back(std::make_shared<T>(event));
    }

    template <class T, typename U>
    void registerEvent(EventType e, T* obj, U callback)
    {
      //auto x = EventGoldCollection(nullptr);
      //(obj->*callback)(x);

      Callback c = (Callback)callback;
      database.insert(std::make_pair(e, std::make_pair(obj, c)));

      //void*(*funcPointerC)() = reinterpret_cast<void*(*)()>(callback);

      //std::pair<Entity*, void(Entity::*)> d = std::pair<Entity*, U>(obj, (void(Entity::*))callback);
      //database.insert(std::make_pair(e, d));

      //callback(U(nullptr));
      //(callback)(nullptr);
      //std::function<void(const U&)> func = std::bind(callback, std::placeholders::_1);
      //std::function<void(const U&)> delegate = std::bind(callback, std::placeholders::_1);
      //database.insert(std::make_pair(e, callback));
    };

    /*
    template <class T>
    void registerEvent(EventType e, EventDelegate delegate)
    {
      //std::function<void(const U&)> delegate = std::bind(callback, std::placeholders::_1);
      //database.insert(std::make_pair(e, callback));
    };
     */
};

#endif //CSCI437_EVENTMANAGER_H