#ifndef CSCI437_MODE_MENU_H
#define CSCI437_MODE_MENU_H

#include "mode.h"
#include "level.h"
#include "level_factory.h"

class MenuMode : public Mode
{

public:
    MenuMode();
    ~MenuMode();
    void update() override;

private:

};


#endif //CSCI437_MODE_MENU_H
