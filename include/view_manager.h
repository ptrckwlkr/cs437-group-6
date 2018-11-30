#ifndef CSCI437_VIEW_MANAGER_H
#define CSCI437_VIEW_MANAGER_H


#include <unordered_map>
#include "events/event_entity_destroyed.h"
#include "view.h"
#include "player_view.h"
#include "view_factory.h"

class ViewManager : public Listener
{

private:
    ViewManager() = default;
    ~ViewManager() = default;
    ViewFactory factory;
    GameLogic *state = nullptr;
    std::shared_ptr<PlayerView> curr_player_view;
    std::unordered_map<long long, std::shared_ptr<View>> views;
    void handleEntityRemoval(const EventEntityDestroyed &event);


public:
    static ViewManager* Instance();
    void init(GameLogic *s);
    void update_views(float delta);
    View &get_view(long long entity_id);
    PlayerView &get_curr_player_view() {return *curr_player_view;}
    std::shared_ptr<PlayerView> &get_player_view(){return curr_player_view;}
    std::vector<std::shared_ptr<View>> get_views();
    void reset() {views.clear();}

    template <class E>
    void add_view(std::shared_ptr<E> &ent)
    {
      std::shared_ptr<Entity> x = ent;
      auto view = factory.create<E>(ent);
      if (view) views.insert(std::pair<long long, std::shared_ptr<View>>(x->id, view));
    }

    template <class T>
    void set_player_view(GameLogic *state, sf::RenderWindow *App)
    {
      curr_player_view = std::make_shared<T>(state, App);
    }
};


#endif //CSCI437_VIEW_MANAGER_H
