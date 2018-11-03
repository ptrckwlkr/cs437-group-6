#ifndef CSCI437_MODE_PLAY_H
#define CSCI437_MODE_PLAY_H

#include "mode.h"
#include "level.h"
#include "level_factory.h"

class PlayMode : public Mode
{

public:
    PlayMode();
    ~PlayMode();
    void update() override;
    std::shared_ptr<Level> get_level() {return level;}

private:
    LevelFactory *level_factory;
    std::shared_ptr<Level> level;

};


#endif //CSCI437_MODE_PLAY_H
