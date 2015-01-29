
#ifndef SDLWRAPPER_APPLICATION_HPP
#define SDLWRAPPER_APPLICATION_HPP

#include <stdint.h>
#include <cstddef>
#include <string>

#include "Resources.hpp"

#define Define_MainApp(appref) \
    sdl::Application * AppHandle = &(appref);

namespace sdl {
    class Event;
    
    class Application {
    public:
        // Command line arguments to the program (shared)
        static std::vector<std::string> Args;
        
    public:
        Application(const std::string &name);
        virtual ~Application();
        
        /**
         * \brief Get the application name.
         */
        virtual const std::string & getName() const;
        
        virtual void init();
        virtual void stop();
        virtual void start() = 0;
        
        /**
         * \brief Implement the main-loop of the application.
         * 
         * This method will call Application::processEvents() as part of its
         * event handling. This method will continue until
         * Application::mRunning is set to false, either by an overloaded
         * method of the Application class or calling Application::quit().
         */
        virtual void mainloop();
        
        /**
         * \brief Process events in the application event buffer.
         * 
         * This method can be called by long-running applications to keep the
         * application responsive. For maximum portability, this should only be
         * called by the main thread.
         */
        virtual void processEvents();
        
        /**
         * \brief Process single event.
         * 
         * This method provides the hook to add custom event handling to the
         * stock event loops. This method should dispatch the event passed to
         * it or deal with it appropriately. Both Application::processEvents
         * and Application::mainloop use this to method to dispatch events.
         */
        virtual void processEvent(Event &e);
        
        /**
         * \brief Signal that the application should quit.
         * 
         * This method will not cause an immediate termination of the
         * application. Instead, a flag is set that will cause the mainloop to
         * terminate on the next iteration.
         */
        virtual void quit();
        
        // app.getResources().getStream();
        Resources & getResources();
        const Resources & getResources() const;
        
    protected:
        virtual void exit();
        
    private:
        const std::string mName;
        bool mRunning;
        Resources mResources;
    };
}

#endif
