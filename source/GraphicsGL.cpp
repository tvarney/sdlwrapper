
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
