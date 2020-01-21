#pragma once

#include <cstring>
#include <stdio.h>
#include <unistd.h>
#include <chrono>
#include <cstdlib>
using _clock            = std::chrono::steady_clock;
using _elapsed          = std::chrono::duration<double>;
using _time             = std::chrono::time_point<_clock, _elapsed>;

using namespace std;

// An animated scene, and the base class for this assignment.
// This can be used to display text on the console in repeated intervals, like
// you would use for a game.
class Scene
{
public:
    static const int WIDTH = 80;
    static const int HEIGHT = 23;

    _time lastUpdated = _clock::now();
    double elapsed = 0.;

    struct BoardCol
    {
        char row[WIDTH];

        char & operator[](int index)
        {
            return row[abs(index) % WIDTH];
        }

        BoardCol & operator=(const BoardCol & other)
        {
            if (this != &other)
            {
                memcpy(row, other.row, WIDTH);
            }
            return *this;
        }
    };

    // All board access is made through a struct to control wrap/clamp
    // behavior for out-of-bounds indices
    struct Board
    {
        BoardCol col[HEIGHT];

        BoardCol & operator[](int index)
        {
            return col[abs(index) % HEIGHT];
        }

        Board & operator=(const Board & other)
        {
            if (this != &other)
            {
                for(int i = 0; i < HEIGHT; i++)
                {
                    col[i] = other.col[i];
                }
            }
            return *this;
        }

        operator const char *()
        {
            return &(col[0][0]);
        }
    };


    // The 2D array that stores the board information. Change the values it
    // holds to change what the scene shows on the screen.
    Board board;

    // You can set this to true to make the board print from bottom to top
    bool flipY = false;

    // You can set this to false in update() to make the scene end.
    bool shouldContinue = true;

    // Keeps track of how many times update() has been called.
    unsigned long frame = 0;

    // If the scene runs for more than this many frames, it will stop.
    // You can set this variable in init() to change the runtime length.
    unsigned long maxFrames = 1000;

    // Frames per second: how many times the scene should update per second.
    // Lower values means fewer updates per second, higher means more.
    // You can set this variable in init( to change the runtime speed.
    double FPS = 60.0;

    // FPS implicitly defines seconds per frame as the inverse
    double SPF() { return 1.0 / FPS; }

    // Writes the contents of the board to the screen
    virtual void showBoard()
    {
        printf("\x1b[H");
        for(int y = 0; y < HEIGHT; y++)
        {
            int ry = (flipY ? (HEIGHT - 1 - y) : y);
            for(int x = 0; x < WIDTH; x++)
            {
                putchar(board[ry][x]);
            }
            putchar('\n');
        }
    }

    // Puts a blank space in every position on the board
    void clearBoard(int xstart = 0, int xend = WIDTH, int ystart = 0, 
        int yend = HEIGHT)
    {
        for(int y = ystart; y < yend; y++)
        {
            for(int x = xstart; x < xend; x++)
            {
                board[y][x] = ' ';
            }
        }
    }

    // Makes the program sleep by the amount of seconds passed in.
    // This gets called in update() to make the scene display more smoothly.
    void sleepFor(double seconds)
    {
        // Convert seconds to microseconds for usleep
        unsigned int ns = (unsigned int)(1000000.0 * seconds);
        usleep(ns);
    }

    // Sets up the scene before it runs
    virtual void init()
    {
        clearBoard();
	    shouldContinue = true;
    }

    // Called to update the scene by a fixed amount of time. 
    virtual void update()
    {
        frame++;
        
        if (frame > maxFrames) shouldContinue = false;
    }
    
    virtual ~Scene() { }

    // The function that sets up and runs the scene. Very concise, but powerful.
    void run()
    {
        init();                     // initialize the scene
        while (shouldContinue)      // start the scene in a loop
        {
            update();               // call update once per loop
            showBoard();            // then see the changes with showBoard()
            sleepFor(SPF());        // then sleep the thread
        }
    }
};
