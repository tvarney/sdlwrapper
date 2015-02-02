
#ifndef SDLWRAP_GRAPHICS_HPP
#define SDLWRAP_GRAPHICS_HPP

#include <stdint.h>

#include "Color.hpp"

namespace sdl {
    class Graphics {
    public:
        virtual ~Graphics();
        
        virtual void clear() = 0;
        virtual void present() = 0;
        
        virtual void setColor(const Color<uint8_t> &color) = 0;
        virtual void setClearColor(const Color<uint8_t> &color) = 0;
        
        virtual void makeCurrent() = 0;
    };
}

#endif
