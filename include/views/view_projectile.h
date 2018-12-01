#ifndef CSCI437_PROJECTILE_VIEW_H
#define CSCI437_PROJECTILE_VIEW_H

#include "view.h"
#include "entities/Projectile.h"

class ProjectileView : public View
{

public:
    ProjectileView(GameLogic *state, Projectile &entity);
    void update(float delta) override;

private:
    Projectile *projectile;


};


#endif //CSCI437_PROJECTILE_VIEW_H
