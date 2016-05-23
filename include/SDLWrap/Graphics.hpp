
#ifndef SDLWRAP_GRAPHICS_HPP
#define SDLWRAP_GRAPHICS_HPP

#include <stdint.h>
#include <geom/Point2.hpp>
#include <geom/Line2.hpp>
#include <geom/Rectangle2.hpp>
//#include <geom/Circle2.hpp>

#include "Color.hpp"

namespace sdl {
    class Graphics {
    public:
        virtual ~Graphics();
        
        virtual void clear();
        virtual void present() = 0;
        
        virtual void setColor(const Color<uint8_t> &color);
        virtual void setClearColor(const Color<uint8_t> &color);
        
        virtual void draw(const geom::Point2d &point);
        virtual void draw(const geom::Line2d &line);
        virtual void draw(const geom::Rectangle2d &rect);
        //virtual void draw(const geom::Circle2d &circle) = 0;
        
        virtual void fill(const geom::Rectangle2d &rect);
        //virtual void fill(const geom::Circle2d &circle) = 0;
        
        virtual void makeCurrent() = 0;
    protected:
        Graphics();
        
        void ortho(double width, double height, double depth = 1.0);
        Color<uint8_t> mFgColor, mClearColor;
    };
}

#endif
