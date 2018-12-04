//
// Created by Ian on 12/2/2018.
//

#ifndef CSCI437_ENEMY_H
#define CSCI437_ENEMY_H

#include "events/event.h"
#include "entities/entity.h"

class Enemy: public Entity
{

public:
    Enemy(float x, float y, float size) : Entity(x, y, size) {
        std::shared_ptr<rapidxml::xml_document<>> doc = resources.GetXMLDoc("enemies");
        buffer = resources.GetXMLBuffer("enemies");
        root_node = (*doc).first_node("Root");
    };

    //represents the kind AI to be used, white (green for orcs) for dumbest AI, red for medium AI, and Gold for best
    std::string type;

    int projectile_damage;

    //distance at which AI stops being passive
    int aggro_dist;


    void updateAttributes() {
        rapidxml::xml_node<> *main_node = root_node->first_node(type.c_str());
        health = std::stoi(main_node->first_node("health")->value());
        speed = std::stoi(main_node->first_node("speed")->value());
        damage = std::stoi(main_node->first_node("contact-damage")->value());
        projectile_damage = std::stoi(main_node->first_node("projectile-damage")->value());
        aggro_dist = std::stoi(main_node->first_node("aggro-dist")->value());
    }

    void setType(const std::string param_type) {
        type.assign(param_type);
        updateAttributes();
    }



};

#endif //CSCI437_ENEMY_H

