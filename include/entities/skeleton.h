#ifndef CSCI437_SKELETON_H
#define CSCI437_SKELETON_H


#include "events/event_collision.h"
#include "events/event_entity_damaged.h"
#include "entity.h"

#define SKELETON_SIZE  20



class Skeleton : public Entity
{

public:
    Skeleton(float x, float y);
    static const EntityType entityType;
    const EntityType& getEntityType() const override {return entityType;}
    void updateAttributes();
    void givePathNodes(std::vector<Vector2D> &path) {path_nodes = path;};
    void setType(std::string param_type);

    int aggro_dist;

    //represents the kind of skeleton, 0 for normal/dumb (white), 1 for smarter (red), and 2 for smartest (gold)
    std::string type;
    std::vector<Vector2D> path_nodes;

private:
    void handleCollision(const EventCollision &event);

};


#endif //CSCI437_SKELETON_H
