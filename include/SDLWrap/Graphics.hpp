
#ifndef SDLWRAP_GRAPHICS_HPP
#define SDLWRAP_GRAPHICS_HPP

#include <stdint.h>

#include "RenderContext.hpp"
#include "Color.hpp"

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
        
        void setFgColor(const Color<uint8_t> &color);
        void setBgColor(const Color<uint8_t> &color);
    protected:
        RenderContext *mContext;
        Color<uint8_t> mFgColor;
        Color<uint8_t> mBgColor;
    };
}

#endif
