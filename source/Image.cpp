
#include "SDLWrap/Image.hpp"

#include <cstring>

using namespace sdl;

Image::Graphics::Graphics(Image &image) :
    mParent(image)
{ }

Image::Graphics::~Graphics() { }

void Image::Graphics::clear() {
    Color<uint8_t> &clearcolor = mClearColor;
    
    if(mParent.mFormat == Image::RGBA) {
        for(uint32_t y = 0; y < mParent.mHeight; ++y) {
            for(uint32_t x = 0; x < mParent.mWidth; ++x) {
                mParent.mBuffer[y * mParent.mPitch + x + 0] = clearcolor.r;
                mParent.mBuffer[y * mParent.mPitch + x + 1] = clearcolor.g;
                mParent.mBuffer[y * mParent.mPitch + x + 2] = clearcolor.b;
                mParent.mBuffer[y * mParent.mPitch + x + 3] = clearcolor.a;
            }
        }
    }else {
        for(uint32_t y = 0; y < mParent.mHeight; ++y) {
            for(uint32_t x = 0; x < mParent.mWidth; ++x) { 
                mParent.mBuffer[y * mParent.mPitch + x + 0] = clearcolor.r;
                mParent.mBuffer[y * mParent.mPitch + x + 1] = clearcolor.g;
                mParent.mBuffer[y * mParent.mPitch + x + 2] = clearcolor.b;
            }
        }
    }
}

void Image::Graphics::present() { }

void Image::Graphics::setColor(const Color<uint8_t> &color) {
    mFgColor = color;
}
void Image::Graphics::setClearColor(const Color<uint8_t> &color) {
    mClearColor = color;
}

void Image::Graphics::makeCurrent() { }
bool Image::Graphics::supportsOpenGL() const {
    return false;
}

uint32_t Image::ByteDepth(enum Image::PixelFormat fmt) {
    switch(fmt) {
    case Image::RGB:
        return 3;
    case Image::RGBA:
        return 4;
    default:
        return 0;
    }
}

Image::Image(uint32_t width, uint32_t height) :
    Image(width, height, width, Image::RGBA, nullptr)
{ }
Image::Image(uint32_t width, uint32_t height, Image::PixelFormat format) :
    Image(width, height, width, format, nullptr)
{ }
Image::Image(uint32_t width, uint32_t height, uint32_t pitch) :
    Image(width, height, pitch, Image::RGBA, nullptr)
{ }
Image::Image(uint32_t width, uint32_t height, uint32_t pitch,
             Image::PixelFormat format) :
    Image(width, height, pitch, format, nullptr)
{ }
Image::Image(uint32_t width, uint32_t height, uint32_t pitch,
             Image::PixelFormat format, uint8_t *data) :
    mWidth(width > 0 ? width : 1), mHeight(height > 0 ? height : 1),
    mPitch(pitch > mWidth ? pitch : width), mBpp(Image::ByteDepth(format)),
    mFormat(format), mBuffer(nullptr), mGraphics(nullptr)
{
    mBuffer = new uint8_t[mPitch * mHeight * mBpp];
    if(data != nullptr) {
        std::memcpy(mBuffer, data, mBpp * mPitch * mHeight);
    }
}

Image::~Image() {
    if(mBuffer != nullptr) {
        delete[] mBuffer;
    }
}

void Image::setPixel(int x, int y, const Color<uint8_t> &color) {
    uint8_t *pbase = mBuffer + ((x + y * mPitch) * mBpp);
    pbase[0] = color.r;
    pbase[1] = color.g;
    pbase[2] = color.b;
    if(mFormat == Image::RGBA) {
        pbase[3] = color.a;
    }
}

Color<uint8_t> Image::getPixel(int x, int y) {
    uint8_t *pbase = mBuffer + ((x + y * mPitch) * mBpp);
    if(mFormat == Image::RGBA) {
        return Color<uint8_t>(pbase[0], pbase[1], pbase[2], pbase[3]);
    }
    return Color<uint8_t>(pbase[0], pbase[1], pbase[2]);
}

sdl::Graphics & Image::getGraphics() {
    if(mGraphics == nullptr) {
        mGraphics = new Image::Graphics(*this);
    }
    return *mGraphics;
}

uint32_t Image::width() const {
    return mWidth;
}
uint32_t Image::height() const {
    return mHeight;
}
uint32_t Image::pitch() const {
    return mPitch;
}
uint32_t Image::bpp() const {
    return mBpp;
}
Image::PixelFormat Image::format() const {
    return mFormat;
}
