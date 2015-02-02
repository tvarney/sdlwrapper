
#ifndef SDLWRAPPER_APPLICATION_HPP
#define SDLWRAPPER_APPLICATION_HPP

#include <stdint.h>
#include <cstddef>
#include <string>

#include "Resources.hpp"

// Basic main method creates an instance of the app then calls run
#define AppMain(appname)              \
    int main(int argc, char **argv) { \
        appname app;                  \
        return app.run(argc, argv);   \
    }

namespace sdl {
    class Event;
    
    struct OpenGLVersion {
        OpenGLVersion(int major_v, int minor_v);
        
        int major_version, minor_version;
    };
    
    class Application {
    private:
        /**
         * \brief Check for SDL initialization status.
         */
        static bool HasInit;
    public:
        /**
         * \brief Enum used for denoting the current point in the  application
         * lifecycle.
         */
        enum Status {
            Stopped,      //< The application is fully stopped
            Initializing, //< The application is starting
            Running,      //< The application is running
            Stopping,     //< The application is shutting down
            Error,        //< The application trapped on an error
        };
        
    public:
        Application(const std::string &name);
        virtual ~Application();
        
        /**
         * \brief Get the application name.
         */
        virtual const std::string & getName() const;
        
        /**
         * \brief Run this application
         * 
         * \arg \c argc The number of arguments on the command line
         * \arg \c argv The actual arguments array
         */
        virtual int run(int argc, char **argv);
        
        /**
         * \brief Signal that the application should quit.
         * 
         * This method will not cause an immediate termination of the
         * application. Instead, a flag is set that will cause the mainloop to
         * terminate on the next iteration.
         */
        virtual void quit();
        
        /**
         * \brief Get application status.
         * \return The application's current status.
         */
        virtual Application::Status getStatus() const;
        
        virtual OpenGLVersion getGLVersion() const;
    protected:
        /**
         * \brief Set the required OpenGL version.
         * 
         * The default OpenGL version to require is 2.1.
         * 
         * \arg \c major The major opengl version to require
         * \arg \c minor The minor opengl version to require
         */
        virtual void requireGLVersion(int major, int minor);
        
        /**
         * \brief Parse command line arguments.
         * 
         * The default behavior is to ignore all arguments.
         */
        virtual void parseArgs(int argc, char **argv);
        
        /**
         * \brief Application callback hook before parsing arguments.
         * 
         * This method is called before any arguments are parsed. This allows
         * the application to set up any needed structures before getting to
         * the parseArgs method.
         */
        virtual void init();
        
        /**
         * \brief Callback hook for app initialization after parsing args.
         * 
         * This method is called immediately before the mainloop, but after the
         * parseArgs method.
         */
        virtual void start();
        
        /**
         * \brief Callback hook for app shutdown.
         * 
         * Any resources allocated by the application should be cleaned up
         * here.
         */
        virtual void stop();
        
        /**
         * \brief Implement the main-loop of the application.
         * 
         * This method will call Application::processEvents() as part of its
         * event handling. This method will continue until
         * Application::mRunning is set to false, either by an overloaded
         * method of the Application class or calling Application::quit().
         */
        virtual void mainLoop();
        
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
        
        // app.getResources().getStream();
        Resources & getResources();
        const Resources & getResources() const;
    private:
        const std::string mName;
        Application::Status mStatus;
        Resources mResources;
    };
}

#endif
