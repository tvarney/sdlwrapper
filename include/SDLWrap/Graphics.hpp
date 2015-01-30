
#ifndef SDLWRAP_GRAPHICS_HPP
#define SDLWRAP_GRAPHICS_HPP

#include "RenderContext.hpp"

namespace sdl {
    class Graphics {
    public:
        /**
         * \brief Create a graphics with the given context
         */
        Graphics(RenderContext *context = nullptr);
        /**
         * \brief Create a copy of the graphics object
         */
        Graphics(const Graphics &source);
        ~Graphics();
        
        Graphics & operator=(const Graphics &source);
        
        bool valid() const;

        void clear();
        void present();
        
        //void setColor();
        //void setClearColor();
    protected:
        RenderContext *mContext;
    };
}

#endif
