
#include "SDLWrap/SDLException.hpp"

#include "SDL_error.h"

using namespace sdl;

SDLException::SDLException() :
    SDLException(std::string())
{ }
SDLException::SDLException(const char *msg) :
    SDLException(std::string(msg))
{ }
SDLException::SDLException(const std::string &message) :
    std::runtime_error("SDLException: " + message + " (SDL: " +
                       std::string(SDL_GetError()) + ")")
{
    SDL_ClearError();
}

SDLException::~SDLException() noexcept { }
