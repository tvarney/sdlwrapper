
#include "SDLWrap/Image.hpp"

using namespace sdl;

Image::ImageGraphics::ImageGraphics(Image &image) :
    mParent(image)
{ }

Image::ImageGraphics::~ImageGraphics() { }

void Image::ImageGraphics::clear() {
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

void Image::ImageGraphics::present() { }

void Image::ImageGraphics::setColor(const Color<uint8_t> &color) {
    mFgColor = color;
}
void Image::ImageGraphics::setClearColor(const Color<uint8_t> &color) {
    mClearColor = color;
}

Image::Image(uint32_t width, uint32_t height, uint32_t pitch,
             Image::PixelFormat format, uint8_t *data) :
    mWidth(width > 0 ? width : 1), mHeight(height > 0 ? height : 1),
    mPitch(pitch > Image::ByteDepth(format) * mWidth ? pitch :
           Image::ByteDepth(format) * mWidth),
    mBuffer(nullptr), mGraphics(nullptr)
{
    if(std::numeric_limits<uint32_t>::max() / mPitch > mHeight) {
        mHeight = std::numeric_limits<uint32_t>::max() / mPitch;
    }
    
    mBuffer = new uint8_t[mPitch * mHeight];
}

