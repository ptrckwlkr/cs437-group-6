#ifndef CSCI437_VIEW_FACTORY_H
#define CSCI437_VIEW_FACTORY_H

#include <memory>
#include <unordered_map>
#include "view.h"
#include "game_logic.h"

namespace ViewFactory
{
    std::shared_ptr<View> createView(GameLogic *state, Entity *entity);
}

#endif //CSCI437_VIEW_FACTORY_H
