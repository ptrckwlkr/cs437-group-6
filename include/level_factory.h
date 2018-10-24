#ifndef CSCI437_LEVEL_FACTORY_H
#define CSCI437_LEVEL_FACTORY_H

#include "level.h"

namespace level_factory
{

    enum Generator
    {
        LEVEL_FILE,
    };

    Level generate_level(Generator algorithm);

}
#endif //CSCI437_LEVEL_FACTORY_H
