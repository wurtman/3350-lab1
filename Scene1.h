#pragma once
#include "Scene.h"
#include <cstring>

// Scene1: makes a text message fall from the top to the bottom of the screen
class MyScene : public Scene
{
    public:
        int start = 0;
        const char * message = "Big whoop";
        const int messageLength = strlen(message);
        virtual void init()
        {
            FPS = 24.0;
            Scene::init();
        }

        // Called once every frame. 
        virtual void update()
        {
            clearBoard();

            for(int i = 0; i < (WIDTH / messageLength); i++)
            {
                int y = start + i;
                if (y < HEIGHT)
                {
                    char * spot = &(board[start + i][i * messageLength]);
                    memcpy(spot, message, messageLength);
                }
            }
            start++;
            
            if (start >= HEIGHT) shouldContinue = false;

            // Keep this call to the parent's version of update()
            Scene::update();
        }
};
