#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <string>
#include <vector>

namespace wm
{
    class Sprite;
    class Window;

    class Sprite 
    {
        private:
            SDL_Texture* img;

            Window &pWindow;

            int ID;
        
        public:
            Sprite( Window &_w, std::string _path );

            bool addFrame( std::string _path );

            void render( SDL_Rect _destRect);

            SDL_Texture* fetchText();

            int getID();

            void free();
    };

    class Window 
    {
        private:
            SDL_Window* window;
            SDL_Renderer* renderer;

            int windowID;

            int w;
            int h;
            
            int x;
            int y;

            std::vector<std::pair<Sprite*, SDL_Rect>> renderPipeline;
            std::vector<Sprite> loadedSprites;
            int spriteCount;

        public:
            Window();
            bool init( int _w, int _h, int _x, int _y, std::string _caption );
            void free();

            bool handleEvent( SDL_Event& e );

            SDL_Renderer* getRenderer();

            int loadSprite( std::string _path );
            int getSpriteCount();
            Sprite fetchSprite( int _id );

            void render();

            void drawSprite( Sprite _spr, int _x, int _y, int _xscale = 1, int _yscale = 1 );
    };

    
} // namespace wm

