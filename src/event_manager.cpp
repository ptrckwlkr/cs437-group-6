#include "EventManager.h"


bool EventManager::AlreadyRegistered( EVENTID eventId, Listener* object){
    
    //start of not registered
    bool alreadyRegistered = false;

    //iterator
    std::pair<std::multimap<EVENTID, Listener*>::iterator,
    std::multimap<EVENTID, Listener*>::iterator> range;

    //all objects that recieve this event
    range = db.equal_range(eventId);

    for (std::multimap<EVENTID, Listener*>::iterator i = range.first; 
        i != range.second; i++){
            
            //if object already subscribed 
            if((*i).second == object){
                alreadyRegistered = true;
                break;
            }
    }
}

//iterate through list of objects to respond to a specific event
void EventManager::DispactchEvent( Event* event){

  //iterator 
    std::pair<std::multimap<EVENTID, Listener*>::iterator,
    std::multimap<EVENTID, Listener*>::iterator> range;

    //find all objects who react to this event
    range = db.equal_range( event->EventId() );

    for ( std::multimap<EVENTID, Listener*>::iterator i = range.first;
        i != range.second; i++){

            //for each object handle the event
            (*i).second ->HandleEvent(event);
        }

}

    //returns an instance of event manager
EventManager* EventManager::Instance(){
    static EventManager instance;
    return &instance;
}

//register object to listen for an event
void EventManager::RegisterObject(EVENTID event, Listener *object){

    //if object is null or it already reigstered, do nothing
    if (!object || AlreadyRegistered(event, object)){
        return;
    }

    //add the object to the database
    db.insert( make_pair(event, object));

}

//unregister an object from an event
void EventManager::UnregisterObject(EVENTID event, Listener *object){

    std::pair<std::multimap<EVENTID, Listener*>::iterator,
    std::multimap<EVENTID, Listener*>::iterator> range;

    range = db.equal_range( event );

    //for each object that can react to the event 
    for ( std::multimap<EVENTID, Listener*>::iterator i = range.first;
        i != range.second; i++){
        //find the object and remove 
        if ( (*i).second == object){
            //delete from database 
            i = db.erase(i);
            break;
        }
    }
}

//unregister an object from all event
void EventManager::UnregisterAll(Listener *object){
    //iterator
    std::multimap<EVENTID, Listener*>::iterator i = db.begin();

    while (i != db.end()){

        //find the correct object
        if ( (*i).second == object){

            //delete
            i = db.erase(i);
        }

        else{
            i++;
        }
    }

}

//send event
void EventManager::SendEvent(EVENTID event, void *data){
    Event newEvent(event, data);
    currentEvents.push_back(newEvent);
}

void EventManager::ProcessEvents(){

    //for each event in list, dispatch the event
    while (currentEvents.size()){
        DispactchEvent(&currentEvents.front());
        //then remove from the list
        currentEvents.pop_front();
    }

}

void EventManager::ClearEvents(){
    //clear the events
    currentEvents.clear();

}

//shuts down the event manager
void EventManager::Shutdown(){

}