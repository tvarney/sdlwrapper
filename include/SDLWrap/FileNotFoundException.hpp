
#ifndef SDLWRAP_FILE_NOT_FOUND_EXCEPTION_HPP
#define SDLWRAP_FILE_NOT_FOUND_EXCEPTION_HPP

#include <stdexcept>
#include "Filesystem.hpp"

namespace sdl {
    class FileNotFoundException : public std::runtime_error {
    public:
        FileNotFoundException(const std::string &message);
        FileNotFoundException(const std::string &message,
                              const filesystem::path &path);
        virtual ~FileNotFoundException();
    };
}

#endif
