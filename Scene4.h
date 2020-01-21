#pragma once
#include "Scene.h"

// Scene4: fills screen based on checkerboard pattern
class MyScene : public Scene
{
    public:
        const int SIZE = 4;
        bool flip = true;
        virtual void init()
        {
            Scene::init();
            FPS = 2.0;
            maxFrames = 10;
        }

        // Called once every frame. 
        virtual void update()
        {
            clearBoard();

            for(int y = 0; y < HEIGHT; y++)
            {
                int yc = y / SIZE;
                bool yeven = yc % 2 == 0;
                for(int x = 0; x < WIDTH; x++)
                {
                    int xc = x / SIZE;
                    bool xeven = xc % 2 == 0;

                    if (xeven == yeven)
                    {
                        board[y][x] = flip ? '@' : '-';
                    }
                    else
                    {
                        board[y][x] = flip ? '_' : '@';
                    }
                }
            }

            flip = !flip;

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
