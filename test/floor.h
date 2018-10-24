#ifndef CSCI437_FLOOR_H
#define CSCI437_FLOOR_H

#define GRID_HEIGHT       100
#define GRID_WIDTH        100
#define MAX_ROOM_DIM      10
#define MIN_ROOM_DIM      3
#define MAX_PASSAGE_LEN   3
#define MIN_PASSAGE_LEN   1
#define MAX_NUM_ROOMS     25
#define MIN_NUM_ROOMS     15

class Floor
{
public:
    explicit Floor(unsigned int seed = 0);
    void print_room();
private:
    char grid[GRID_HEIGHT][GRID_WIDTH];
    void generate_rooms();
};


#endif //CSCI437_FLOOR_H
