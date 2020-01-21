#include "MyScene.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>

namespace Scene1 
{
#include "Scene1.h"
}

namespace Scene2
{
#include "Scene2.h"
}

namespace Scene3
{
#include "Scene3.h"
}

namespace Scene4
{
#include "Scene4.h"
}

namespace Scene5
{
#include "Scene5.h"
}

int main()
{
    printf("\x1b[2J");

    Scene * scenes[] = 
    {
        new Scene1::MyScene(),
        new Scene2::MyScene(),
        new Scene3::MyScene(),
        new Scene4::MyScene(),
        new Scene5::MyScene()
    };

    for(auto scene : scenes)
    {
        scene->run();
    }

    for(auto & scene : scenes)
    {
        delete scene;
    }

    return 0;
}

