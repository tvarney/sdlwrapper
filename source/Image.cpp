
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

void Image::Graphics::draw(const geom::Point2d &point) {
    mParent.setPixel(point.x, point.y, mFgColor);
}
void Image::Graphics::draw(const geom::Line2d &line) {
    
}
void Image::Graphics::draw(const geom::Rectangle2d &rect) {
    uint32_t width = rect.dim.width;
    uint32_t x1 = rect.origin.x;
    uint32_t x2 = x1 + width;
    uint32_t y1 = rect.origin.y;
    uint32_t y2 = y1 + rect.dim.height;
    uint32_t a2 = 255 - mFgColor.a;
    uint32_t pdiff = mParent.mBpp * (mParent.mPitch - mParent.mWidth + x1);
    uint8_t *p = mParent.mBuffer + (x1 + y1 * mParent.mPitch) * mParent.mBpp;
    
    // Precompute alpha multiplied color values
    uint32_t ra = mFgColor.r * ((uint32_t)mFgColor.a);
    uint32_t ga = mFgColor.g * ((uint32_t)mFgColor.a);
    uint32_t ba = mFgColor.b * ((uint32_t)mFgColor.a);
    
    switch(mParent.format()) {
    case Image::RGB:
        /* Draw top line */
        for(uint32_t x = x1; x <= x2; ++x) {
            p[0] = (p[0] * a2 + ra) >> 8;
            p[1] = (p[1] * a2 + ga) >> 8;
            p[2] = (p[2] * a2 + ba) >> 8;
            p += 3;
        }
        /* Draw middle vertical lines */
        p += pdiff;
        for(uint32_t y = y1 + 1; y < y2; ++y) {
            p[0] = (p[0] * a2 + ra) >> 8;
            p[1] = (p[1] * a2 + ga) >> 8;
            p[2] = (p[2] * a2 + ba) >> 8;
            
            p[0 + width] = (p[0 + width] * a2 + ra) >> 8;
            p[1 + width] = (p[1 + width] * a2 + ra) >> 8;
            p[2 + width] = (p[2 + width] * a2 + ra) >> 8;
            
            p += pdiff;
        }
        /* Draw bottom line */
        for(uint32_t x = x1; x < x2; ++x) {
            p[0] = (p[0] * a2 + ra) >> 8;
            p[1] = (p[1] * a2 + ga) >> 8;
            p[2] = (p[2] * a2 + ba) >> 8;
            p += 3;
        }
        break;
    case Image::RGBA:
        /* Draw top line */
        for(uint32_t x = x1; x <= x2; ++x) {
            p[0] = (p[0] * a2 + ra) >> 8;
            p[1] = (p[1] * a2 + ga) >> 8;
            p[2] = (p[2] * a2 + ba) >> 8;
            p[3] = p[3] + mFgColor.a;
            p += 4;
        }
        /* Draw middle vertical lines */
        p += pdiff;
        for(uint32_t y = y1 + 1; y < y2; ++y) {
            p[0] = (p[0] * a2 + ra) >> 8;
            p[1] = (p[1] * a2 + ga) >> 8;
            p[2] = (p[2] * a2 + ba) >> 8;
            p[3] = p[3] + mFgColor.a;
            
            p[0 + width] = (p[0 + width] * a2 + ra) >> 8;
            p[1 + width] = (p[1 + width] * a2 + ra) >> 8;
            p[2 + width] = (p[2 + width] * a2 + ra) >> 8;
            p[3 + width] = p[3 + width] + mFgColor.a;
            
            p += pdiff;
        }
        /* Draw bottom line */
        for(uint32_t x = x1; x < x2; ++x) {
            p[0] = (p[0] * a2 + ra) >> 8;
            p[1] = (p[1] * a2 + ga) >> 8;
            p[2] = (p[2] * a2 + ba) >> 8;
            p[3] = p[3] + mFgColor.a;
            
            p += 4;
        }
        break;
    }
}

void Image::Graphics::fill(const geom::Rectangle2d &rect) {
    uint32_t x1 = rect.origin.x;
    uint32_t x2 = x1 + rect.dim.width;
    uint32_t y1 = rect.origin.y;
    uint32_t y2 = y1 + rect.dim.height;
    uint32_t a2 = 255 - mFgColor.a;
    uint32_t pdiff = mParent.mBpp * (mParent.mPitch - mParent.mWidth + x1);
    uint8_t *p = mParent.mBuffer + (x1 + y1 * mParent.mPitch) * mParent.mBpp;
    
    // Precompute the alpha*color
    uint32_t ra = mFgColor.r * ((uint32_t)mFgColor.a);
    uint32_t ga = mFgColor.g * ((uint32_t)mFgColor.a);
    uint32_t ba = mFgColor.b * ((uint32_t)mFgColor.a);
    
    switch(mParent.format()) {
    case Image::RGB:
        for(uint32_t y = y1; y < y2; ++y) {
            for(uint32_t x = x1; x <= x2; ++x) {
                p[0] = (p[0] * a2 + ra) >> 8;
                p[1] = (p[1] * a2 + ga) >> 8;
                p[2] = (p[2] * a2 + ba) >> 8;
                p += 3;;
            }
            p += pdiff;
        }
        break;
    case Image::RGBA:
        for(uint32_t y = y1; y < y2; ++y) {
            for(uint32_t x = x1; x <= x2; ++x) {
                p[0] = (p[0] * a2 + ra) >> 8;
                p[1] = (p[1] * a2 + ga) >> 8;
                p[2] = (p[2] * a2 + ba) >> 8;
                p[3] = p[3] + mFgColor.a;
                
                p += 4;
            }
            p += pdiff;
        }
        break;
    }
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
