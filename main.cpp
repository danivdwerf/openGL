#include <iostream>
#include "./Assets/_Scripts/Main.h"

void onWindowResize()
{
    glViewport(0, 0, 0, 0);
}


int main(int argc, char** argv)
{
    Main* game = new Main("OpenGL", 640, 360);
    if(!game)
        return -1;

    game->setFramerate(60);
    game->mainloop();
    return 0;
}