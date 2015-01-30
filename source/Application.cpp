
#include "SDLWrap/Application.hpp"

#include <SDL.h>

#include "SDLWrap/Event.hpp"
#include "SDLWrap/SDLException.hpp"
#include "SDLWrap/Window.hpp"

using namespace sdl;

bool Application::HasInit = false;

Application::Application(const std::string &name) :
    mName(name), mStatus(Application::Stopped)
{
    // Attempt to initialize SDL if it hasn't already been done
    if(Application::HasInit == false) {
        if(0 != SDL_Init(SDL_INIT_EVERYTHING)) {
            throw SDLException("Failed to initialize SDL");
        }
        std::atexit(SDL_Quit);
        Application::HasInit = true;
    }
}
Application::~Application() { }

const std::string & Application::getName() const {
    return mName;
}

int Application::run(int argc, char **argv) {
    mStatus = Application::Initializing;
    try {
        // Initialize the application
        init();
        // Parse the arguments
        parseArgs(argc, argv);
        // Start Hook
        start();
        // Set our status to Running
        mStatus = Application::Running;
        // Main event loop of the application
        mainLoop();
        mStatus = Application::Stopping;
    }catch(std::exception &e) {
        mStatus = Application::Error;
        // Attempt to call stop()
        stop();
        throw e;
    }
    stop();
    Window::KillAll();
    
    return 0;
}

void Application::quit() {
    mStatus = Application::Stopping;
}

Application::Status Application::getStatus() const {
    return mStatus;
}

void Application::parseArgs(int argc, char **argv) { }

void Application::init() { }
void Application::start() { }
void Application::stop() { }

void Application::mainLoop() {
    Event e;
    while(mStatus == Application::Running) {
        while(Event::Poll(e)) {
            processEvent(e);
        }
        Window::UpdateAll();
    }
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
        quit();
        break;
    default:
        break;
    }
}
