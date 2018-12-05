#ifndef CSCI437_VIEW_SREEP_PROJECTILE_H
#define CSCI437_VIEW_SREEP_PROJECTILE_H


#include "view.h"
#include "entities/sreep_projectile.h"

class SreepProjectileView : public View
{

public:
    SreepProjectileView(GameLogic *state, SreepProjectile &entity);
    void update(float delta) override;

private:
    SreepProjectile *projectile;


};


#endif //CSCI437_VIEW_SREEP_PROJECTILE_H
