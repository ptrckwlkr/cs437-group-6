#ifndef CSCI437_VIEW_MANAGER_H
#define CSCI437_VIEW_MANAGER_H


#include "view.h"
#include "player_view.h"
#include "game_logic.h"

class ViewManager
{
private:
    ViewManager();
    ~ViewManager() = default;
    std::set<std::shared_ptr<View>> views;
    std::shared_ptr<PlayerView> player_view;
    GameLogic *state;


public:
    static ViewManager* Instance();
    void init(GameLogic *s) {state = s;}
    void set_player_view(std::shared_ptr<PlayerView> &view) {player_view = view;}
    void remove_view(long long view_id);
    std::shared_ptr<PlayerView> &get_player_view(){return player_view;}
    std::set<std::shared_ptr<View>> &get_views() {return views;}
    void clear() {views.clear();}

    template <class E, class V>
    void add_view(std::shared_ptr<E> &ent)
    {
      auto view = std::make_shared<V>(state, *ent);
      views.insert(view);
    }
};


#endif //CSCI437_VIEW_MANAGER_H
