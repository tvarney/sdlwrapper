
#include "SDLWrap/Graphics.hpp"

#include <SDL_render.h>
#include "SDLWrap/Renderable.hpp"

using namespace sdl;

Graphics::Graphics(RenderContext *context) :
    mContext(context), mFgColor(255, 255, 255), mBgColor(0, 0, 0)
{ }
Graphics::Graphics(const Graphics &source) :
    mContext(source.mContext), mFgColor(source.mFgColor),
    mBgColor(source.mBgColor)
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
    SDL_SetRenderDrawColor(mContext, mBgColor.r, mBgColor.g, mBgColor.b,
                           mBgColor.a);
    SDL_RenderClear(mContext);
    SDL_SetRenderDrawColor(mContext, mFgColor.r, mFgColor.g, mFgColor.b,
                           mFgColor.a);
}

void Graphics::present() {
    SDL_RenderPresent(mContext);
}

void Graphics::setFgColor(const Color<uint8_t> &color) {
    mFgColor = color;
    SDL_SetRenderDrawColor(mContext, mFgColor.r, mFgColor.g, mFgColor.b,
                           mFgColor.a);
}
void Graphics::setBgColor(const Color<uint8_t> &color) {
    mBgColor = color;
}
