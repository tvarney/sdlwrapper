
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
        
        virtual void clear() = 0;
        virtual void present() = 0;
        
        virtual void setColor(const Color<uint8_t> &color) = 0;
        virtual void setClearColor(const Color<uint8_t> &color) = 0;
        
        virtual void draw(const geom::Point2d &point) = 0;
        virtual void draw(const geom::Line2d &line) = 0;
        virtual void draw(const geom::Rectangle2d &rect) = 0;
        //virtual void draw(const geom::Circle2d &circle) = 0;
        
        virtual void fill(const geom::Rectangle2d &rect) = 0;
        //virtual void fill(const geom::Circle2d &circle) = 0;
        
        virtual void makeCurrent() = 0;
        virtual bool supportsOpenGL() const = 0;
    };
}

#endif
