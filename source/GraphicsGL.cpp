
#include "SDLWrap/GraphicsGL.hpp"

#include <SDL_video.h>
#include <SDL_opengl.h>

using namespace sdl;

void GraphicsGL::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsGL::setColor(const Color<uint8_t> &color) {
    mFgColor = color;
    glColor4b(color.r, color.g, color.b, color.r);
}

void GraphicsGL::setClearColor(const Color<uint8_t> &color) {
    mClearColor = color;
    mClearColor.a = 255; //< Lock clear color to full alpha
    glClearColor(color.r, color.g, color.b, color.a);
}

void GraphicsGL::draw(const geom::Point2d &point) {
    glBegin(GL_POINTS); {
        glVertex2d(point.x, point.y);
    } glEnd();
}
void GraphicsGL::draw(const geom::Line2d &line) {
    glBegin(GL_LINES); {
        glVertex2d(line.p1.x, line.p1.y);
        glVertex2d(line.p2.x, line.p2.y);
    } glEnd();
}
void GraphicsGL::draw(const geom::Rectangle2d &rect) {
    double x1 = rect.origin.x;
    double x2 = x1 + rect.dim.width;
    double y1 = rect.origin.y;
    double y2 = y1 + rect.dim.height;
    glBegin(GL_LINE_LOOP); {
        glVertex2d(x1, y1);
        glVertex2d(x2, y1);
        glVertex2d(x2, y2);
        glVertex2d(x1, y2);
    } glEnd();
}

void GraphicsGL::fill(const geom::Rectangle2d &rect) {
    double x1 = rect.origin.x;
    double x2 = x1 + rect.dim.width;
    double y1 = rect.origin.y;
    double y2 = y1 + rect.dim.height;
    glBegin(GL_QUADS); {
        glVertex2d(x1, y1);
        glVertex2d(x2, y1);
        glVertex2d(x2, y2);
        glVertex2d(x1, y2);
    } glEnd();
}

bool GraphicsGL::supportsOpenGL() const {
    return true;
}

void GraphicsGL::ortho(double width, double height, double depth) {
    glOrtho(0.0, width, height, 0.0, 0.0, depth);
}
