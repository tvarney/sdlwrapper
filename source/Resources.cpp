
#include "SDLWrap/Resources.hpp"

#include <algorithm>
#include <boost/filesystem.hpp>
#include <cstddef>

#include "SDLWrap/FileNotFoundException.hpp"

using namespace sdl;

#ifdef PLATFORM_DARWIN
# define DEFAULT_LOCATION "../Resources/"
#else
# define DEFAULT_LOCATION "../data/"
#endif
const filesystem::path Resources::sDefaultPath(DEFAULT_LOCATION);

filesystem::path operator+(const filesystem::path &p1,
                           const filesystem::path &p2)
{
    filesystem::path r = p1;
    r /= p2;
    return r;
}

Resources::Resources() {
    addPath(std::string(DEFAULT_LOCATION));
}
Resources::~Resources() { }

bool Resources::getStream(const filesystem::path &path,
                          /* OUT */ filesystem::ifstream &ifsout) const
{
    // Locate file - Check paths then archives
    filesystem::path fpath;
    for(const filesystem::path &p : mDirList) {
        fpath = p + path;
        if(filesystem::exists(fpath)) {
            ifsout.open(fpath);
            return true;
        }
    }
    
    throw FileNotFoundException("Could not locate resource: ", path);
}

void Resources::addPath(const filesystem::path &path) {
    mDirList.push_back(path);
}

void Resources::removePath(const filesystem::path &path) {
    auto iter = std::find(mDirList.begin(), mDirList.end(), path);
    if(iter != mDirList.end()) {
        mDirList.erase(iter);
    }
}
