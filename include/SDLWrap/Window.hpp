
#ifndef SDLWRAPPER_WINDOW_HPP
#define SDLWRAPPER_WINDOW_HPP

#include <SDL_video.h>
#include <stdint.h>
#include <cstddef>
#include <string>

namespace sdl {
    class Application;
    
    class Window {
    public:
        static const int Anywhere;
        static const int Centered;
        
    public:
        Window(Application &app);
        Window(Application &app, const std::string &title);
        Window(Application &app, const std::string &title, int width,
               int height);
        Window(Application &app, const std::string &title, int width,
               int height, int x, int y);
        ~Window();
        
        void hide();
        void show();
        void swap();
        
        void makeCurrent();
        
        uint32_t getId();
    private:
        SDL_Window *mWinHandle;
        SDL_GLContext mGLContext;
    };
}

#endif
