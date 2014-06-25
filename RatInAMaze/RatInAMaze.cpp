/*
* Abhishek Bansal
* 6.18.2014
*/

/*
* A Maze is given as N*N binary matrix of blocks where source block is the upper left most block i.e., maze[0][0] and 
* destination block is lower rightmost block i.e., maze[N-1][N-1]. A rat starts from source and has to reach destination. 
* The rat can move only in two directions: forward and down.
* In the maze matrix, 0 means the block is dead end and 1 means the block can be used in the path from source to destination. 
* Note that this is a simple version of the typical Maze problem. For example, a more complex version can be that the rat 
* can move in 4 directions and a more complex version can be with limited number of moves.
* Ref: http://www.geeksforgeeks.org/backttracking-set-2-rat-in-a-maze/
*/

#include <iostream> 

#define MAZE_SIZE 4

int maze1[][MAZE_SIZE] ={{1, 0, 0, 0},
                         {1, 1, 0, 1},
                         {0, 1, 0, 0},
                         {1, 1, 1, 1}};

int solMaze1[][MAZE_SIZE] ={{0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0},
                            {0, 0, 0, 0}};

bool isSafe(int x, int y)
{
    if ( x >= 0 && x < MAZE_SIZE && y >= 0 && y < MAZE_SIZE && maze1[x][y] == 1)
        return true;
    return false;
}


// my dirty solution :(
// first attempt at backtracking
void findPath(int x, int y)
{
    int nextX, nextY;

    if((x == (MAZE_SIZE - 1)) && (y == (MAZE_SIZE - 1)) )
    {
        // we have reached destination
        solMaze1[x][y] = 1;
        std::cout << std::endl << "Destination Reached !!";
        return;
    }

    nextX = x + 1;
    if(isSafe(nextX, y))
    {
        solMaze1[x][y] = 1;
        findPath(nextX, y);
        return;
    }

    nextY = y + 1;
    if(isSafe(x, nextY))
    {
        solMaze1[x][y] = 1;
        findPath(x, nextY);
        return;
    }
    else
    {
        solMaze1[x][y] = 0;
        return;
    }
}

/*
* Better solution by geek for geeks
* http://www.geeksforgeeks.org/backttracking-set-2-rat-in-a-maze/
* Note that it is assumed that rat can only move downwards or right
*/

/* A recursive utility function to solve Maze problem */
bool solveMazeUtil(int x, int y)
{
    // if (x,y is goal) return true
    if(x == MAZE_SIZE-1 && y == MAZE_SIZE-1)
    {
        solMaze1[x][y] = 1;
        return true;
    }
 
    // Check if maze[x][y] is valid
    if(isSafe(x, y) == true)
    {
        // mark x,y as part of solution path
        solMaze1[x][y] = 1;
 
        /* Move forward in x direction */
        if (solveMazeUtil(x+1, y) == true)
            return true;
 
        /* If moving in x direction doesn't give solution then
           Move down in y direction  */
        if (solveMazeUtil(x, y+1) == true)
            return true;
 
        /* If none of the above movements work then BACKTRACK: 
            unmark x,y as part of solution path */
        solMaze1[x][y] = 0;
        return false;
    }   
 
    return false;
}


/* A utility function to print solution matrix sol[N][N] */
void printSolution()
{
    for (int x = 0; x < MAZE_SIZE; x++)
    {
        for (int y = 0; y < MAZE_SIZE; y++)
            printf(" %2d ", solMaze1[x][y]);
        printf("\n");
    }
}

void solveMaze()
{
    //findPath(0,0);
    solveMazeUtil(0, 0);
    printSolution();
}

/* A utility function to check if i,j are valid indexes for BOARD_SIZE*BOARD_SIZE chessboard */

int main()
{
    solveMaze();
    return 0;
}