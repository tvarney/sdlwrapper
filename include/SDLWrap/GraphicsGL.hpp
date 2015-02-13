
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
        
        virtual void draw(const geom::Point2d &point);
        virtual void draw(const geom::Line2d &line);
        virtual void draw(const geom::Rectangle2d &rect);
        //virtual void draw(const geom::Circle2d &circle);
        
        virtual void fill(const geom::Rectangle2d &rect);
        //virtual void fill(const geom::Circle2d &circle);
        
        virtual bool supportsOpenGL() const;
    protected:
        /**
         * Call this in the make-current method of a GL based graphics class
         * when making it current?
         */
        void ortho(double width, double height, double depth = 1.0);
        
        Color<uint8_t> mFgColor, mClearColor;
    };
}

#endif
