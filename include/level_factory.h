#ifndef CSCI437_LEVEL_FACTORY_H
#define CSCI437_LEVEL_FACTORY_H

#include <fstream>
#include "level.h"

enum Generator
{
    LEVEL_FILE,
};

class LevelFactory
{

public:
    LevelFactory() = default;
    void set_algorithm(Generator algorithm) {this->algorithm = algorithm;};
    std::shared_ptr<Level> generate_level();

private:
    std::shared_ptr<Map> load(std::string filename);
    Generator algorithm;

};

#endif //CSCI437_LEVEL_FACTORY_H
