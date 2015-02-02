
#ifndef SDLWRAP_GRAPHICS_GL_HPP
#define SDLWRAP_GRAPHICS_GL_HPP

#include "Graphics.hpp"

namespace sdl {
    /**
     * \brief Base class of TextureGraphics and WindowGraphics.
     */
    class GraphicsGL : public Graphics {
    public:
        virtual void clear();
        
        virtual void setColor(const Color<uint8_t> &color);
        virtual void setClearColor(const Color<uint8_t> &color);
    protected:
        Color<uint8_t> mFgColor, mClearColor;
    };
}

#endif
