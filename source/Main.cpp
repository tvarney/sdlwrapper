
#include "SDLWrap/Application.hpp"
#include "SDLWrap/SDLException.hpp"

#include <SDL.h>

extern int ProgramStart(void);

int main(int argc, char **argv) {
    for(int i = 0; i < argc; i++) {
        sdl::Application::Args.emplace_back(argv[i]);
    }
    
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw sdl::SDLException("Could not initialize SDL Subsystems: ");
    }
    
    return ProgramStart();
}
