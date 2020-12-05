#include "Maze.h"

/**
* Constructor
* Starts creation of new bitStream (maze)
* 00000
* 01010
* 01010
* 01110
* 00000
*
* The calloc() function shall allocate unused space for an array of nelem elements each of whose size in bytes is elsize. The space shall be initialized to all bits 0.
*
* Allocates memory space for an array of size (width * height) the array elements size of maze struct
*/

BitMaze::BitMaze(int width, int height)
{
    maze_t maze;
    maze = (maze_t) calloc (width * height, sizeof (cell_t));
    this->CreateMaze (maze, width, height);
    this->PrintMaze (maze, width, height);
    free (maze);
}


/**
* Destructs the maze
*/

BitMaze::~BitMaze()
{
    cout << endl << "          \033[35;2m~Deconstructing Maze\033[0m " << endl;
}


/**
* creates a new maze by visiting and random allocating areas of the struct to 1
*
* @param maze the array maze struct
* @param width of the maze
* @param height of the maze
*
* @return void
*
*/

void BitMaze::CreateMaze (maze_t maze, int width, int height)
{
    maze_t mp, maze_top;
    char paths [4];
    int visits, directions;

    visits = width * height - 1;
    mp = maze;
    maze_top = mp + (width * height) - 1;

    while (visits) {
        directions = 0;

        if ((mp - width) >= maze && cell_empty (mp - width))
            paths [directions++] = UP;
        if (mp < maze_top && ((mp - maze + 1) % width) && cell_empty (mp + 1))
            paths [directions++] = RIGHT;
        if ((mp + width) <= maze_top && cell_empty (mp + width))
            paths [directions++] = DOWN;
        if (mp > maze && ((mp - maze) % width) && cell_empty (mp - 1))
            paths [directions++] = LEFT;

        if (directions) {
            visits--;
            directions = ((unsigned) rand () % directions);

            switch (paths [directions]) {
                case UP:
                    mp->up = TRUE;
                    (mp -= width)->down = TRUE;
                    break;
                case RIGHT:
                    mp->right = TRUE;
                    (++mp)->left = TRUE;
                    break;
                case DOWN:
                    mp->down = TRUE;
                    (mp += width)->up = TRUE;
                    break;
                case LEFT:
                    mp->left = TRUE;
                    (--mp)->right = TRUE;
                    break;
                default:
                    break;
            }
        } else {
            do {
                if (++mp > maze_top)
                    mp = maze;
            } while (cell_empty (mp));
        }
    }
}


/**
* Once the maze is created assign this in the vector quadrant lines
* for easy access by the main class
*
* @param maze the struct array
* @param width of the maze struct
* @param heigth of the maze struct
*
* @return void
*/

void BitMaze::PrintMaze (maze_t maze, int width, int height)
{
    int w, h;
    char *line, *lp;

    line = (char *) calloc ((width + 1) * 2, sizeof (char));

    maze->up = TRUE;
    (maze + (width * height) - 1)->down = TRUE;

    for (lp = line, w = 0; w < width; w++) {
        *lp++ = '0';
        if ((maze + w)->up)
            *lp++ = ((maze + w)->path) ? '1' : '0';
        else
            *lp++ = '0';
    }
    *lp++ = '0';
    this->quadrantLines.push_back(line);
    for (h = 0; h < height; h++) {
        for (lp = line, w = 0; w < width; w++) {
            if ((maze + w)->left)
                *lp++ = ((maze + w)->path && (maze + w - 1)->path) ? '0' : '1';
            else
                *lp++ = '0';
            *lp++ = ((maze + w)->path) ? '0' : '1';
        }
        *lp++ = '0';
        this->quadrantLines.push_back(line);
        for (lp = line, w = 0; w < width; w++) {
            *lp++ = '0';
            if ((maze + w)->down)
                *lp++ = ((maze + w)->path && (h == height - 1 || (maze + w + width)->path)) ? '0' : '1';
            else
                *lp++ = '0';
        }
        *lp++ = '0';
        this->quadrantLines.push_back(line);
        maze += width;
    }
    free (line);
}


/**
* returns a position in the quadrant vector
*
* @param int row
* @param int col
*
* @return char 0 or 1
*/

char BitMaze::getQuandrantLocationVal(int row, int col)
{
    string rowVal = this->quadrantLines[row];
    return rowVal[col];
}

