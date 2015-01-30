
#include "SDLWrap/Graphics.hpp"

#include <SDL_render.h>
#include "SDLWrap/Renderable.hpp"

using namespace sdl;

Graphics::Graphics(RenderContext *context) :
    mContext(context)
{ }
Graphics::Graphics(const Graphics &source) :
    mContext(source.mContext)
{ }
Graphics::~Graphics() { }

Graphics & Graphics::operator=(const Graphics &source) {
    mContext = source.mContext;
    return *this;
}

bool Graphics::valid() const {
    return (mContext != nullptr);
}

void Graphics::clear() {
    //SDL_SetRenderDrawColor(mBgColor.r, mBgColor.g, mBgColor.b, mBgColor.a);
    SDL_RenderClear(mContext);
    //SDL_SetRenderDrawColor(mFgColor.r, mFgColor.g, mFgColor.b, mFgColor.a);
}

void Graphics::present() {
    SDL_RenderPresent(mContext);
}
