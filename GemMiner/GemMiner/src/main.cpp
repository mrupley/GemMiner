#include <stdio.h>

#include "GameWindow.h"

using namespace std;


int main( int argc, char* args[] )
{
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        srand(time(0));
        GameWindow gameWindow;
        gameWindow.load();
    }
    
    return 0;
}