#ifndef CSCI437_LEVEL_FILE_H
#define CSCI437_LEVEL_FILE_H

#include <string>
#include <vector>
#include "level.h"

class LevelFile : public Level
{

public:
    LevelFile();

private:
    char* load(std::string filename);
    std::vector<std::vector<char>> grid;
};


#endif //CSCI437_LEVEL_FILE_H
