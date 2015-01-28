
#include "SDLWrap/Application.hpp"
#include "SDLWrap/SDLException.hpp"

#include <SDL.h>

extern sdl::Application * AppHandle;

int main(int argc, char **argv) {
    // Grab the arguments
    for(int i = 0; i < argc; i++) {
        sdl::Application::Args.emplace_back(argv[i]);
    }
    
    // We init everything by default
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw sdl::SDLException("Could not initialize SDL Subsystems: ");
    }
    
    //TODO: Wrap this stuff so we handle any exception relatively gracefully
    AppHandle->start();
    AppHandle->mainloop();
    
    return 0;
}
