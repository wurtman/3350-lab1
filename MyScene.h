#pragma once

#include "Scene.h"

// A child of the Scene class to make a new animated scene.
// Feel free to add any new member functions or variables to MyScene.
class MyScene : public Scene
{
    protected:

	int x = 0;
	int y = 0;
        // Called once when the scene begins.
        virtual void init()
        {
            // Keep this call to the parent's version of init()
            Scene::init();
            // Your code here


        }

        // Called once every frame. 
        virtual void update()
        {
            // Your code here
	    clearBoard();
	    board[y][x] = 'x';
	    x++;





            // Keep this call to the parent's version of update()
            Scene::update();
        }
};
