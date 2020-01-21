#pragma once
#include "Scene.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

double rfloat()
{
    return (rand() % 1025) / 1024.0;
}

double lerp(double t, double a, double b)
{
    return ((1.0 - t) * a) + (t * b);
}

// Scene3: bouncing balls of varying bounciness
class MyScene : public Scene
{
    public:
        const double gravity = -9.81;
        // first dimension is for the col, second dimension contains 
        // position in [0], velocity in [1], and bounciness in [2]
        double physics[WIDTH][3];

        bool firstBounce = false;

        virtual void init()
        {
            Scene::init();

            srand(time(0));

	    FPS = 30.0;
	    maxFrames = 400;

            for(int x = 0; x < WIDTH; x++)
            {
                physics[x][0] = HEIGHT - 1;         // position
                physics[x][1] = 0;                  // velocity
                physics[x][2] = rfloat() * 0.99;    // bounciness
            }
        }

        // Called once every frame. 
        virtual void update()
        {
            clearBoard();

            int restCount = 0;

            double dt = SPF();

            for(int x = 0; x < WIDTH; x++)
            {
                int y = (int)physics[x][0];
                if (y < 0 ) y = 0;
                else if (y >= HEIGHT) y = HEIGHT - 1;

                board[HEIGHT - 1 - y][x] = 'o';

                // explicit integration
                double oldv = physics[x][1];
                double newv = oldv + (gravity * dt);
                double oldp = physics[x][0];
                double newp = oldp + (newv * dt);

                // Check for bounce
                if (newp <= 0)
                {
                    newp = abs(newp);              // preserve bounce offset
                    newv = -newv * physics[x][2];  // flip velocity direction
                    physics[x][2] *= 0.75;         // dampen velocity

                    firstBounce = true;
                }

                physics[x][0] = newp;
                physics[x][1] = newv;

                if (abs(newp) <= 0.1 && abs(newv - oldv) <= 0.5) restCount++;
            }
            
            if (firstBounce && restCount == WIDTH) shouldContinue = false;

            // Keep this call to the parent's version of update()
            Scene::update();
        }
};
