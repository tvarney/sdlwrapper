
#ifndef SDLWRAPPER_SDLEXCEPTION_HPP
#define SDLWRAPPER_SDLEXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace sdl {
    class SDLException : public std::runtime_error {
    public:
        SDLException();
        SDLException(const char *msg);
        SDLException(const std::string &message);
        virtual ~SDLException() noexcept;
    };
}

#endif
