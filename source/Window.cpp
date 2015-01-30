
#include "SDLWrap/Window.hpp"

#include <SDL_video.h>
#include <SDL_render.h>

#include "SDLWrap/Application.hpp"
#include "SDLWrap/SDLException.hpp"

using namespace sdl;

int const Window::Anywhere = SDL_WINDOWPOS_UNDEFINED;
int const Window::Centered = SDL_WINDOWPOS_CENTERED;

std::map<uint32_t, Window *> Window::WindowMap;
Window * Window::sActiveHandle;

Window & Window::Create(const std::string &title, int width, int height) {
    return *(new Window(title, width, height, Window::Anywhere,
                        Window::Anywhere));
}
Window & Window::Create(const std::string &title, int width, int height,
                              int x, int y)
{
    return *(new Window(title, width, height, x, y));
}

Window * Window::ById(uint32_t id) {
    auto iter = WindowMap.find(id);
    if(iter == WindowMap.end()) {
        return nullptr;
    }
    return iter->second;
}

void Window::KillAll() {
    while(WindowMap.size() > 0) {
        delete (WindowMap.begin()->second);
    }
}

Window * Window::Active() {
    return sActiveHandle;
}

void Window::UpdateAll() {
    for(auto wptr : WindowMap) {
        wptr.second->update();
    }
}

Window::Window(const std::string &title, int width, int height, int x, int y) :
    mWinHandle(nullptr)
{
    mWinHandle = SDL_CreateWindow(title.data(), x, y, width, height, 0);
    if(mWinHandle == nullptr) {
        throw SDLException("Failed to create window: ");
    }
    
    mWinId = SDL_GetWindowID(mWinHandle);
    // The window is registered at the end of the creation process to make sure
    // that an invalid broken window isn't registered.
    
    // Add the mapping to ourself
    WindowMap[mWinId] = this;
}

Window::~Window() {
    // Remove ourself from the window mapping
    // At this point, any reference to the window by this id is undefined
    WindowMap.erase(WindowMap.find(mWinId));
    
    hide();
    
    SDL_DestroyWindow(mWinHandle);
    mWinHandle = nullptr;
}

void Window::hide() {
    SDL_HideWindow(mWinHandle);
}

void Window::show() {
    SDL_ShowWindow(mWinHandle);
}

uint32_t Window::getId() const {
    return mWinId;
}

void Window::update() {
    Graphics &g = this->getGraphics();
    g.clear();
    // root->update(g);
    g.present();
}

RenderContext * Window::getContext() {
    mContext = SDL_CreateRenderer(mWinHandle, -1,
                                  SDL_RENDERER_ACCELERATED);
    return mContext;
}
