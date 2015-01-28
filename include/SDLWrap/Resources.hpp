
#ifndef SDLWRAP_RESOURCES_HPP
#define SDLWRAP_RESOURCES_HPP

#include <vector>

#include "Filesystem.hpp"

namespace sdl {
    /**
     * \brief Class that manages access to resources.
     * 
     * TODO: Add support for adding archive files. 7zip SDK
     */
    class Resources {
    public:
        static const filesystem::path sDefaultPath;
        
    public:
        Resources();
        ~Resources();
        
        bool getStream(const filesystem::path &path,
                       /*OUT*/ filesystem::ifstream &ifsout) const;
        
        void addPath(const filesystem::path &path);
        void removePath(const filesystem::path &path);
        void clearPaths();
    protected:
        std::vector<filesystem::path> mDirList;
    };
}

#endif
