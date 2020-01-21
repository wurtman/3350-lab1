#pragma once
#include "Scene.h"
#include <cstdlib>
#include <ctime>

// Scene5: random walk that leaves a trail where it's been.
class MyScene : public Scene
{
    public:
        int x = WIDTH / 2;
        int y = HEIGHT / 2;
        virtual void init()
        {
            Scene::init();

            maxFrames = 500;

            srand(time(0));
        }

        // Called once every frame. 
        virtual void update()
        {
            char oldC = board[y][x];
            char newc = ' ';
            switch(oldC)
            {
                case ' ':
                    newc = '.';
                    break;
                case '.':
                    newc = '-';
                    break;
                case '-':
                    newc = '+';
                    break;
                case '+':
                    newc = '#';
                    break;
                case '#':
                    newc = '0';
                    break;
                default:
                    newc = '.';
                    break;
            }
            board[y][x] = newc;

            int nx = (rand() % 3) - 1;
            int ny = (rand() % 3) - 1;

            x += nx;
            y += ny;

            if (x < 0) x = 0;
            if (x >= WIDTH) x = WIDTH - 1;

            if (y < 0) y = 0;
            if (y >= HEIGHT) y = HEIGHT - 1;

            // Keep this call to the parent's version of update()
            Scene::update();
        }

        // Writes the contents of the board to the screen
        virtual void showBoard()
        {
            printf("\x1b[H");
            for(int y = 0; y < HEIGHT; y++)
            {
                for(int x = 0; x < WIDTH; x++)
                {
                    putchar(board[HEIGHT - 1 - y][x]);
                }
                putchar('\n');
            }
        }
};
