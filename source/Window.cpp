
#include "SDLWrap/Window.hpp"

#include <SDL_video.h>
#include <SDL_render.h>

#include "SDLWrap/Application.hpp"
#include "SDLWrap/SDLException.hpp"

using namespace sdl;

static SDL_GLContext gOpenGLContext = nullptr;

//------------------//
// Static Variables //
//------------------//
int const Window::Anywhere = SDL_WINDOWPOS_UNDEFINED;
int const Window::Centered = SDL_WINDOWPOS_CENTERED;

std::map<uint32_t, Window *> Window::WindowMap;
Window * Window::sActiveHandle;

//------------//
// Static API //
//------------//
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

std::size_t Window::NumWindows() {
    return WindowMap.size();
}

//---------------------//
// Window Graphics API //
//---------------------//
Window::WindowGraphics::WindowGraphics(Window &window) :
    mWindow(window)
{
    // Make sure we have a context.
    if(gOpenGLContext == nullptr) {
        gOpenGLContext = SDL_GL_CreateContext(window.mWinHandle);
    }
}
Window::WindowGraphics::~WindowGraphics() { }

void Window::WindowGraphics::present() {
    SDL_GL_SwapWindow(mWindow.mWinHandle);
}
void Window::WindowGraphics::makeCurrent() {
    SDL_GL_MakeCurrent(mWindow.mWinHandle, gOpenGLContext);
}

//------------//
// Window API //
//------------//
Window::Window(const std::string &title, int width, int height, int x, int y) :
    mWinHandle(nullptr), mGraphics(nullptr)
{
    mWinHandle = SDL_CreateWindow(title.data(), x, y, width, height,
                                  SDL_WINDOW_OPENGL);
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

Graphics & Window::getGraphics() {
    if(mGraphics == nullptr) {
        mGraphics = new WindowGraphics(*this);
    }
    
    return *mGraphics;
}

ViewManager & Window::getViewManager() {
    return mManager;
}

void Window::update() {
    Graphics &g = this->getGraphics();
    g.makeCurrent();
    g.clear();
    // root->update(g);
    g.present();
}
