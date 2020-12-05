#ifndef MAZE_H_
#define MAZE_H_

#include <stdlib.h> // free calloc rand
#include <sstream> // string stream 
#include <vector>
#include <iostream>
#include <string>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#ifdef TRUE
#undef TRUE
#endif 
#define TRUE 1

// macro function
#define cell_empty(a) (!(a)->up && !(a)->right && !(a)->down && !(a)->left)

using std::cout;
using std::string;
using std::vector;
using std::endl;

typedef struct {
        unsigned int up      : 1;
        unsigned int right   : 1;
        unsigned int down    : 1;
        unsigned int left    : 1;
        unsigned int path    : 1;
        unsigned int visited : 1;
} cell_t;
typedef cell_t *maze_t;


class BitMaze
{
    private:
        void CreateMaze (maze_t maze, int width, int height);
        void PrintMaze (maze_t maze, int width, int height);
        vector <string> quadrantLines;

    public:
        BitMaze(int width, int height);
        ~BitMaze();
        char getQuandrantLocationVal(int row, int col);
};


#endif /*MAZE_H_*/
