
#ifndef SDLWRAPPER_WINDOW_HPP
#define SDLWRAPPER_WINDOW_HPP

//#include <SDL_video.h>
#include <stdint.h>
#include <cstddef>
#include <map>
#include <string>

#include "Renderable.hpp"
#include "GraphicsGL.hpp"

extern "C" struct SDL_Window;

namespace sdl {
    /**
     * \brief A renderable window.
     */
    class Window : public Renderable {
    private:
        
        /**
         * \brief The OpenGL graphics context used with windows.
         */
        class WindowGraphics : public GraphicsGL {
        public:
            WindowGraphics(Window &window);
            virtual ~WindowGraphics();
            
            virtual void present();
            virtual void makeCurrent();
        private:
            Window &mWindow;
        };
        
        static std::map<uint32_t, Window *> WindowMap;
        static Window * sActiveHandle;
    public:
        static const int Anywhere;
        static const int Centered;
        
        /**
         * \brief Create a window with the given title, width and height.
         * 
         * \arg \c title The window title.
         * \arg \c w The width of the window
         * \arg \c h The height of the window
         */
        static Window & Create(const std::string &title, int w, int h);
        static Window & Create(const std::string &title, int width, int height,
                               int x, int y);
        
        /**
         * \brief Get the window that matches the ID given
         * \arg \c id The ID of the window to get.
         * \return The window if it exists, otherwise nullptr.
         */
        static Window * ById(uint32_t id);
        /**
         * \brief Destroy and delete all windows
         */
        static void KillAll();
        
        /**
         * \brief Get the active window.
         */
        static Window * Active();
        
        /**
         * \brief Update all windows.
         * 
         * This method iterates over all open windows in arbitrary order,
         * calling their Window::update() method.
         */
        static void UpdateAll();
        
        /**
         * \brief Get the number of open windows.
         */
        static std::size_t NumWindows();
        
    public:
        virtual ~Window();
        
        virtual void hide();
        virtual void show();
        
        virtual uint32_t getId() const;
        
        virtual void update();
        
        virtual Graphics & getGraphics();
    protected:
        Window(const std::string &title, int width, int height, int x, int y);
        
        SDL_Window *mWinHandle;
        WindowGraphics *mGraphics;
        uint32_t mWinId; //< Cached window ID
    };
}

#endif
