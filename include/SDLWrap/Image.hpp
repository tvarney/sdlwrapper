
#ifndef SDLWRAP_IMAGE_HPP
#define SDLWRAP_IMAGE_HPP

#include <stdint.h>

#include "Color.hpp"
#include "Graphics.hpp"
#include "Renderable.hpp"

namespace sdl {
    /**
     * \brief A renderable image class.
     * 
     * For ease of implementation, all image types except RGBA8888 and RGB888
     * are ignored.
     */
    class Image : public Renderable {
    public:
        enum PixelFormat {
            RGB,
            RGBA,
        };
        
        class Graphics : public sdl::Graphics {
        public:
            Graphics(Image &image);
            virtual ~Graphics();
            
            void clear();
            void present();
            
            void setColor(const Color<uint8_t> &color);
            void setClearColor(const Color<uint8_t> &color);
            
            void draw(const geom::Point2d &point);
            void draw(const geom::Line2d &line);
            void draw(const geom::Rectangle2d &rect);
            //void draw(const geom::Circle2d &circle);
            
            void fill(const geom::Rectangle2d &rect);
            //void fill(const geom::Circle2d &circle);
            
            void makeCurrent();
            bool supportsOpenGL() const;
        protected:
            Image & mParent;
            Color<uint8_t> mFgColor, mClearColor;
        };
        
    public:
        static uint32_t ByteDepth(enum PixelFormat fmt);
        
    public:
        /**
         * \brief Create a new RGBA image of the given width and height.
         * 
         * The pitch of the image is given as the width of the image.
         * 
         * \arg \c width The width of the image to create.
         * \arg \c height The height of the image to create.
         */
        Image(uint32_t width, uint32_t height);
        /**
         * \brief Create a new image of the given width, height and format.
         * 
         * The pitch of the image will be the same as the height.
         * 
         * \arg \c width The width of the new image
         * \arg \c height The height of the image
         * \arg \c format The pixel format for the image.
         */
        Image(uint32_t width, uint32_t height, Image::PixelFormat format);
        /**
         * \brief Create a new RGBA image of the given width, height and pitch.
         * 
         * The pitch must be > the width. The difference between the pitch and
         * the width describes the number of empty bytes between the end of the
         * pixel data and then end of a row in the image.
         * In general, a pitch where there are no extra bytes will be equal to
         *   pitch = width * (format == PixelFormat::RGBA ? 4 : 3);
         * Any extra will translate into bytes past the end of the buffer.
         * 
         * \arg \c width The width of the image
         * \arg \c height The height of the image
         * \arg \c pitch The pitch of the image
         */
        Image(uint32_t width, uint32_t height, uint32_t pitch);
        /**
         * \brief Create a new image with the given width, height, pitch and
         * format.
         * 
         * \arg \c width The width of the image to create
         * \arg \c height The height of the image to create
         * \arg \c pitch The pitch of the image
         * \arg \c format The pixel format of the image
         */
        Image(uint32_t width, uint32_t height, uint32_t pitch,
              Image::PixelFormat format);
        /**
         * \brief Create a new image with the given width, height, pitch and
         * format.
         */
        Image(uint32_t width, uint32_t height, uint32_t pitch,
              Image::PixelFormat format, uint8_t *data);
        virtual ~Image();
        
        void setPixel(int x, int y, const Color<uint8_t> &color);
        Color<uint8_t> getPixel(int x, int y);
        
        virtual sdl::Graphics & getGraphics();
        
        uint32_t width() const;
        uint32_t height() const;
        uint32_t pitch() const;
        uint32_t bpp() const;
        Image::PixelFormat format() const;
    protected:
        uint32_t mWidth, mHeight, mPitch, mBpp;
        Image::PixelFormat mFormat;
        uint8_t *mBuffer;
        Image::Graphics *mGraphics;
    };
}

#endif
