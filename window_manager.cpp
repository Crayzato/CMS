#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <string>
#include <vector>

#include "iostream"

#include "window_manager.hpp"

using namespace wm;

// Sprite
Sprite::Sprite( Window& _w, std::string _path )
:pWindow{_w}{
    bool success = true;

    std::string p = "images\\" + _path;
    SDL_Texture* tempImg = NULL;

    ID = pWindow.getSpriteCount();

    totalFrames = 1;
    currFrame = 0;

    SDL_Surface* loadedSurface = IMG_Load( p.c_str() );
    if ( loadedSurface == NULL ) { success = false; }
    else
    {
        tempImg = SDL_CreateTextureFromSurface( pWindow.getRenderer(), loadedSurface );
        if( tempImg == NULL ) { success = false; }
        SDL_FreeSurface( loadedSurface );
        img.emplace_back( tempImg );
    }
}

bool Sprite::addFrame( std::string _path )
{
    bool success = true;

    std::string p = "images\\" + _path;
    SDL_Texture* tempImg = NULL;

    SDL_Surface* loadedSurface = IMG_Load( p.c_str() );
    if ( loadedSurface == NULL ) { success = false; }
    else
    {
        tempImg = SDL_CreateTextureFromSurface( pWindow.getRenderer(), loadedSurface );
        if( tempImg == NULL ) { success = false; }
        SDL_FreeSurface( loadedSurface );
        img.emplace_back( tempImg );
    }
    totalFrames ++;

    return success;
}

void Sprite::render( SDL_Rect _destRect, int frame ) {
    if ( frame == -1 ) { currFrame = ( currFrame + 1 >= totalFrames ) ? 0 : currFrame + 1; }
    else { currFrame = frame; }
    SDL_RenderCopy( pWindow.getRenderer(), img[currFrame], NULL, &_destRect );
}

SDL_Texture* Sprite::fetchText( int frame )
{
    if ( frame >= 0 ) { return img[frame]; }
    else { return img[currFrame]; }
}

int Sprite::getID()
{
    return ID;
}

void Sprite::free()
{
    for ( int i = 0; i < totalFrames; i++ )
    {
        SDL_DestroyTexture( img[i] );
        img[i] = NULL;
    }
}


// Window
Window::Window()
{
    window = NULL;
    renderer = NULL;

    spriteCount = 0;

    w = 0;
    h = 0;

    x = 0;
    y = 0;
}

bool Window::init( int _w, int _h, int _x, int _y, std::string _caption )
{
    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow( _caption.c_str(), _x, _y, _w, _h, flags );
    if ( window != NULL )
    {
        w = _w;
        h = _h;

        x = _x;
        y = _y;

        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        if ( renderer == NULL )
        {
            SDL_DestroyWindow( window );
            window = NULL;
        }
        else
        {
            SDL_SetRenderDrawColor( renderer, 20, 20, 20, 0xFF );
            windowID = SDL_GetWindowID( window );
        }

    }
    return window != NULL && renderer != NULL;
}

void Window::free()
{
    for ( int i = 0; i < loadedSprites.size(); i++ ) { loadedSprites[i].free(); }
    SDL_DestroyRenderer( renderer );
    renderer = NULL;
    SDL_DestroyWindow( window );
    window = NULL;
}

bool Window::handleEvent( SDL_Event& e )
{
    bool success = true;
    if( e.type == SDL_WINDOWEVENT && e.window.windowID == windowID )
    {
        switch( e.window.event )
        {
            case SDL_WINDOWEVENT_CLOSE: 
                success = false;
                SDL_HideWindow( window );
            break;
        }
    }
    return success;
}

SDL_Renderer* Window::getRenderer()
{
    return renderer;
}

int Window::loadSprite( std::string _path )
{
    Sprite s( *this, _path );
    loadedSprites.emplace_back(s);
    spriteCount ++;
    return s.getID();
}

int Window::getSpriteCount()
{
    return spriteCount;
}

Sprite Window::fetchSprite( int _id )
{
    return loadedSprites.at(_id);
}

void Window::drawSprite( Sprite _spr, int _x, int _y, int _xscale, int _yscale )
{
    SDL_Rect dRect;
    dRect.x = _x;
    dRect.y = _y;
    SDL_QueryTexture( _spr.fetchText(), NULL, NULL, &dRect.w, &dRect.h );
    dRect.w *= _xscale;
    dRect.h *= _yscale;

    Sprite* sprPtr = &_spr;

    renderPipeline.emplace_back( std::make_pair( sprPtr, dRect ) );
}

void Window::render()
{
    SDL_RenderClear( renderer );
    for ( int i = 0; i < renderPipeline.size(); i++ )
    {
        Sprite* spr = renderPipeline[i].first;
        (*spr).render( renderPipeline[i].second );
    }
    renderPipeline.clear();
    SDL_RenderPresent( renderer );
    
}

