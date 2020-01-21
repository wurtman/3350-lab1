#pragma once
#include "Scene.h"
#include <cstdlib>
#include <ctime>

// Scene 2: Conway's Game of Life
class MyScene : public Scene
{
    public:
        Board nextBoard;
        int initialAlive = (HEIGHT * WIDTH) / 10;

        virtual void init()
        {
            Scene::init();

            maxFrames = 600;

            FPS = 60.0;

            srand(time(0));

            int count = 0;
            while (count < initialAlive)
            {
                int x = rand() % WIDTH;
                int y = rand() % HEIGHT;

                if (!isAlive(y, x))
                {
                    board[y][x] = 'o';
                    count++;
                }
            }
        }

        bool isAlive(int y, int x)
        {
            return board[y][x] == 'o';
        }

        // Follow's Conway's game of life to update the board.
        // See https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Rules
        bool checkCell(int y, int x)
        {
            int numNeighbors = 0;

            // Check all 8 neighbors
            for(int i = -1; i < 2; i++)
            {
                int yo = y + i;
                if (yo < 0 || yo >= HEIGHT) continue;
                for(int j = -1; j < 2; j++)
                {
                    int xo = x + j;
                    if (xo < 0 || xo >= WIDTH) continue;
                    if (xo == x && yo == y) continue;

                    if (board[yo][xo] == 'o')
                    {
                        numNeighbors++;
                    }
                }
            }

            if (isAlive(y, x))
            {
                if (numNeighbors == 2 || numNeighbors == 3) return true;
                else return false;
            }
            else if (numNeighbors == 3)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        // Called once every frame. 
        virtual void update()
        {
            int aliveCount = 0;

            for(int y = 0; y < HEIGHT; y++)
            {
                for(int x = 0; x < WIDTH; x++)
                {
                    bool cellAlive = checkCell(y, x);
                    nextBoard[y][x] = (cellAlive ? 'o' : ' ');

                    if (cellAlive)
                    {
                        aliveCount++;
                    }
                }
            }

            if (aliveCount == 0) shouldContinue = false;

            board = nextBoard;

            // Keep this call to the parent's version of update()
            Scene::update();
        }
};
