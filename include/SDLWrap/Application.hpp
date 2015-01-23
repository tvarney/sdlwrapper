
#ifndef SDLWRAPPER_APPLICATION_HPP
#define SDLWRAPPER_APPLICATION_HPP

#include <stdint.h>
#include <cstddef>
#include <map>
#include <string>
#include <vector>

namespace sdl {
    class Window;
    
    class Application {
    private:
        static const char *sDefaultResourceDir;
        
    public:
        // Command line arguments to the program (shared)
        static std::vector<std::string> Args;
        
    public:
        Application(const std::string &name);
        virtual ~Application();
        
        virtual const std::string & getName() const;
        
        virtual void mainloop();
    private:
        const std::string name;
        std::map<uint32_t, Window *> mWindowMap;
        std::vector<std::string> mResourceDirs;
    };
}

#endif
