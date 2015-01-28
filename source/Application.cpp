
#include "SDLWrap/Application.hpp"

#include "SDLWrap/Event.hpp"
#include "SDLWrap/Window.hpp"

using namespace sdl;

Application::Application(const std::string &name) :
    mName(name)
{ }
Application::~Application() { }

const std::string & Application::getName() const {
    return mName;
}

void Application::init() { }
void Application::stop() { }

void Application::mainloop() {
    Event e;
    
    while(Application::mRunning) {
        while(Event::Poll(e)) {
            processEvent(e);
        }
    }
    
    exit();
}

void Application::processEvents() {
    Event e;
    while(Event::Poll(e)) {
        processEvent(e);
    }
}

void Application::processEvent(Event &e) {
    switch(e.type()) {
    case Event::Quit:
        mRunning = false;
        
        break;
    default:
        break;
    }
}

void Application::quit() {
    mRunning = false;
}

void Application::exit() {
    // Call our stop-hook
    stop();
    // Kill all windows when exiting
    Window::KillAll();
}
