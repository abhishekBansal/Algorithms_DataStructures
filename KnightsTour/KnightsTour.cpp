/*
* Abhishek Bansal
* 6.17.2014
* Knights tour using backtracking
*/

/*
* A knight's tour is a sequence of moves of a knight on a chessboard such that the knight visits every square 
* only once. If the knight ends on a square that is one knight's move from the beginning square (so that it could 
* tour the board again immediately, following the same path), the tour is closed, otherwise it is open. 
*/

/*
* solution from http://www.geeksforgeeks.org/backtracking-set-1-the-knights-tour-problem/
* CAUTION: Its too too Slow :(
*/

#include <iostream>

#define BOARD_SIZE 8

// knights initial position
static const unsigned int InitialX = 0;
static const unsigned int InitialY = 0;

// take 2d array as a reference
void initialize(int (&chessBoard)[BOARD_SIZE][BOARD_SIZE])
{
    // initialize array with all -1 s
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            chessBoard[i][j] = -1;
        }
    }
}

/* A utility function to check if i,j are valid indexes for BOARD_SIZE*BOARD_SIZE chessboard */
int isSafe(int x, int y, int (&sol) [BOARD_SIZE][BOARD_SIZE])
{
    if ( x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && sol[x][y] == -1)
        return 1;
    return 0;
}

/* A utility function to print solution matrix sol[N][N] */
void printSolution(int (&sol) [BOARD_SIZE][BOARD_SIZE])
{
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
            printf(" %2d ", sol[x][y]);
        printf("\n");
    }
}

/* A recursive utility function to solve Knight Tour problem */
int recurseKT(int x, int y, int movei, int (&sol)[BOARD_SIZE][BOARD_SIZE], int xMove[BOARD_SIZE], int yMove[BOARD_SIZE])
{
    int nextX, nextY;

    // stopping condition
    // if all moves have been made return true
    if(movei == BOARD_SIZE * BOARD_SIZE)
        return true;

    for(int i=0; i < BOARD_SIZE; i++)
    {
        nextX = x + xMove[i];
        nextY = y + yMove[i];
        if(isSafe(nextX, nextY, sol))
        {
            sol[nextX][nextY] = movei;
            if(recurseKT(nextX, nextY, movei + 1, sol, xMove, yMove) == true)
                return true;
            else
                // backtrack
                sol[nextX][nextY] = -1;
        }
    }

    //std::cout << std::endl << "Wrong Path.. Backtrack !!";
    // can't move further and all moves have not been made this was a wrong path return false
    return false;
}

void solveKT()
{
    int chessBoard[BOARD_SIZE][BOARD_SIZE];
    initialize(chessBoard);

    /* xMove[] and yMove[] define next move of Knight.
       xMove[] is for next value of x coordinate
       yMove[] is for next value of y coordinate */
    int xMove[8] = {  2, 1, -1, -2, -2, -1,  1,  2 };
    int yMove[8] = {  1, 2,  2,  1, -1, -2, -2, -1 };

    chessBoard[InitialX][InitialY] = 0;

    /* Start from 0,0 and explore all tours using solveKTUtil() */
    if(recurseKT(0, 0, 1, chessBoard, xMove, yMove) == false)
    {
        printf("Solution does not exist");
        return;
    }
    else
        printSolution(chessBoard);
}

int main()
{
    solveKT();  
    return 0;
}