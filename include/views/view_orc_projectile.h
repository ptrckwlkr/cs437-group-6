#ifndef CSCI437_VIEW_ORC_PROJECTILE_H
#define CSCI437_VIEW_ORC_PROJECTILE_H


#include "view.h"
#include "entities/orc_projectile.h"

class OrcProjectileView : public View
{

public:
    OrcProjectileView(GameLogic *state, OrcProjectile &entity);
    void update(float delta) override;

private:
    OrcProjectile *projectile;


};


#endif //CSCI437_VIEW_ORC_PROJECTILE_H
