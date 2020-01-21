#ifdef SCENE1
#include "Scene1.h"
#elif SCENE2 
#include "Scene2.h"
#elif SCENE3 
#include "Scene3.h"
#elif SCENE4 
#include "Scene4.h"
#elif SCENE5
#include "Scene5.h"
#else
#include "MyScene.h"
#endif

using namespace std;

int main()
{
    printf("\x1b[2J");

    Scene * scene = new MyScene();

    scene->run();

    return 0;
}

