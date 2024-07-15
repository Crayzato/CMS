#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <string>
#include <vector>

#include "iostream"

#include "window_manager.hpp"
#include "data.hpp"

// Function Declarations
bool init();
void loadGraphics();
void close();

// Constants
const int SC_W = 640;
const int SC_H = 384;

const std::string IMAGEPATHS[] = {
    "player.png"
};

enum PATHS {
    test,
    total
};

// Global Variables
wm::Window window;

int main( int argc, char *argv[] )
{
    if ( init() )
    {
        SDL_Event e;
        bool run = true;
        while ( run )
        {
            while ( SDL_PollEvent( &e ) != 0 ) {
                if ( e.type == SDL_QUIT ) { run = false; }
                if ( !window.handleEvent( e ) ) { run = false; }
            }
            window.render();
        }
    }
    close();
    return 0;
}

// Function Definitions
bool init()
{
    bool success = true;
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if ( !window.init( SC_W, SC_H, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, "Database Initialisation" ) ) { success = false; }
        else
        {
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) ) 
            {
                printf( "SDL_image could not initialize... SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }
            loadGraphics();
        }
    }
    return success;
}

void loadGraphics()
{
    for ( int i = 0; i < PATHS::total; i++ )
    {
        int id = window.loadSprite( IMAGEPATHS[i] );
        //if ( !window.fetchSprite( id ).addFrame( "player2.png" ) ) { printf( "Error" ); }
    }
}

void close()
{
    window.free();
    IMG_Quit();
    SDL_Quit();
}
