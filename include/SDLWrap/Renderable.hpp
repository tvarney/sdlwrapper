
#ifndef SDLWRAP_RENDERABLE_HPP
#define SDLWRAP_RENDERABLE_HPP

namespace sdl {
    class Graphics;
    
    class Renderable {
    public:
        Renderable();
        virtual ~Renderable();
        
        virtual Graphics & getGraphics() = 0;
    protected:
        Graphics *mGraphics;
    };
}

#endif
