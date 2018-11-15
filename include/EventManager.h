#ifndef CSCI437_EVENTMANAGER_H
#define CSCI437_EVENTMANAGER_H

#include <SFML/Window/Event.hpp>
#include <list>
#include <map>
#include "event.h"
#include "entity.h"

class EventManager
{
    private: 
        //stores objects and their events
        std::multimap<EVENTID, Entity*> db;

        //list of events that need to be processed 
        std::list<Event> currentEvents;

        EventManager() {};
        ~EventManager() { this->Shutdown(); }

        //copies constructor
        // EventManager( const EventManager& rhs){};
        // EventManager& operator = ( const EventManager& rhs){};

        //helper
        bool AlreadyRegistered( EVENTID event, Entity* object);

        //will dispatch events 
        void DispactchEvent( Event* event);
        
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
};

#endif //CSCI437_EVENTMANAGER_H