
#include "SDLWrap/Renderable.hpp"

#include <SDL_render.h>

using namespace sdl;

Renderable::Renderable() { }
Renderable::~Renderable() {
    // Make sure we kill the context
    if(mGraphics.valid()) {
        SDL_DestroyRenderer(mContext);
    }
}

Graphics & Renderable::getGraphics() {
    if(false == mGraphics.valid()) {
        mGraphics = Graphics(this->getContext());
    }
    return mGraphics;
}
