#ifndef CSCI437_ANIMATION_FACTORY_H
#define CSCI437_ANIMATION_FACTORY_H

#include <memory>
#include "entities/entity.h"
#include "Animations/Animation.h"

namespace AnimationFactory
{
    std::shared_ptr<Animation> createAnimation(Entity *entity);
}

#endif //CSCI437_ANIMATION_FACTORY_H
