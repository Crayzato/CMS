#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <string>
#include <vector>

#include "iostream"

#include "window_manager.hpp"
#include "terminal_input.hpp"
#include "data.hpp"

// Function Declarations
bool init();
void loadGraphics();
void close();

// Constants
const int SC_W = 640;
const int SC_H = 384;

const std::string IMAGEPATHS[] = {
    "player.png",
    "player2.png"
};

enum PATHS {
    test,
    total
};

// Global Variables
wm::Window window;

data::Bin bin("data.json");
term::TerminalStart start(bin);

int main( int argc, char *argv[] )
{
    bool run = true;
    while ( run ) {
        start.getcmd();
        if ( start.performAction() == -1 ) { run = false; }
    }
    bin.close();
    /*
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
    */
   return 0;
}

// Function Definitions
bool init()
{
    printf( "initialising application" );
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
    }
}

void close()
{
    window.free();
    IMG_Quit();
    SDL_Quit();
}
