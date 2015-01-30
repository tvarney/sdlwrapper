
#ifndef SDLWRAP_RENDERABLE_HPP
#define SDLWRAP_RENDERABLE_HPP

#include "Graphics.hpp"
#include "RenderContext.hpp"

namespace sdl {
    class Renderable {
    public:
        Renderable();
        
        virtual ~Renderable();
        Graphics & getGraphics();
    protected:
        virtual RenderContext * getContext() = 0;
        
        Graphics mGraphics;
        RenderContext *mContext;
    };
}

#endif
