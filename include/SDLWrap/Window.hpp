
#ifndef SDLWRAPPER_WINDOW_HPP
#define SDLWRAPPER_WINDOW_HPP

//#include <SDL_video.h>
#include <stdint.h>
#include <cstddef>
#include <map>
#include <string>

#include "SDLWrap/Renderable.hpp"

extern "C" struct SDL_Window;

namespace sdl {
    class Window : public Renderable {
    private:
        static std::map<uint32_t, Window *> WindowMap;
        static Window * sActiveHandle;
        
    public:
        static const int Anywhere;
        static const int Centered;
        
        static Window & Create(const std::string &title, int width,
                               int height);
        static Window & Create(const std::string &title, int width, int height,
                               int x, int y);
        static Window * ById(uint32_t id);
        static void KillAll();
        
        static Window * Active();
        
        static void UpdateAll();
    public:
        virtual ~Window();
        
        virtual void hide();
        virtual void show();
        
        virtual uint32_t getId() const;
        
        virtual void update();
    protected:
        Window(const std::string &title, int width, int height, int x, int y);
        virtual RenderContext * getContext();
        
        SDL_Window *mWinHandle;
        
        // Cached so we don't call a method each time we want the id
        uint32_t mWinId;
    };
}

#endif
